#include <algorithm>
#include <RendererVulkan.hpp>
#include <iostream>
#include "ShaderVulkan.hpp"
#include <stdexcept>
#include <renderer/PhysicalDevice.hpp>

namespace
{
    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;

    VkExtent2D Extent(sx::Surface::Extent ex)
    {
        VkExtent2D extent;
        extent.width = ex.width;
        extent.height = ex.height;

        return extent;
    }
}

namespace sx
{
    RendererVulkan::RendererVulkan(PhysicalDeviceVulkan& pdevice, SurfaceVulkan& surface, const std::vector<uint32_t>& vertex, const std::vector<uint32_t>& fragment)
         : surface(surface)
        , device(pdevice)
    {
        swapchain.Init(device, surface);
        renderPass.Init(device, swapchain, surface);

        VkViewport viewport = {};
        viewport.width = static_cast<float>(surface.CurrentExtent().width);
        viewport.height = static_cast<float>(surface.CurrentExtent().height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        ShaderVertexVulkan vertexShader(device, vertex);
        ShaderFragmentVulkan fragmentShader(device, fragment);
        pipeline.Init(device, renderPass, surface, vertexShader, fragmentShader, viewport);

        commandBuffers.resize(swapchain.NumberOfImages());
        VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
        commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocateInfo.pNext = nullptr;
        commandBufferAllocateInfo.commandPool = device.CommandPool();
        commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        commandBufferAllocateInfo.commandBufferCount = swapchain.ImageViews().size();
        vkAllocateCommandBuffers(device, &commandBufferAllocateInfo, commandBuffers.data());

        VkSemaphoreCreateInfo semaphoreInfo = {};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
            vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS)
            throw std::runtime_error("failed to create semaphores!");

    }

    RendererVulkan::~RendererVulkan()
    {
        vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
        vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);
    }

    void RendererVulkan::RecordDrawingCommands(const VkBuffer& buffer, std::size_t verticesCount)
    {
        for (size_t i = 0; i < commandBuffers.size(); i++)
        {
            VkCommandBufferBeginInfo beginInfo = {};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

            vkBeginCommandBuffer(commandBuffers[i], &beginInfo);

            VkRenderPassBeginInfo renderPassInfo = {};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = renderPass;
            renderPassInfo.framebuffer = renderPass.FrameBuffers()[i];
            renderPassInfo.renderArea.offset = { 0, 0 };
            renderPassInfo.renderArea.extent = Extent(surface.CurrentExtent());

            VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 0.0f };
            renderPassInfo.clearValueCount = 1;
            renderPassInfo.pClearValues = &clearColor;

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
            vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

            VkDeviceSize offset = 0;
            vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, &buffer, &offset);
            vkCmdDraw(commandBuffers[i], verticesCount, 1, 0, 0);

            //vkCmdBindIndexBuffer(commandBuffers[i], buffers[1], 0, VK_INDEX_TYPE_UINT32);
            //vkCmdDrawIndexed(commandBuffers[i], indicesCount, 1, 0, 0, 0);

            vkCmdEndRenderPass(commandBuffers[i]);
            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
                throw std::runtime_error("failed to record command buffer!");
        }
    }

    void RendererVulkan::Draw()
    {
        uint32_t imageIndex;
        vkAcquireNextImageKHR(device, swapchain, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkCommandBuffer cmd = commandBuffers[imageIndex];
        VkPipelineStageFlags waitStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = &imageAvailableSemaphore;
        submitInfo.pWaitDstStageMask = &waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &cmd;
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &renderFinishedSemaphore;

        vkQueueSubmit(device.Queue(), 1, &submitInfo, VK_NULL_HANDLE);

        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &renderFinishedSemaphore;
        presentInfo.swapchainCount = 1;
        VkSwapchainKHR swapchainKHR = swapchain;
        presentInfo.pSwapchains = &swapchainKHR;
        presentInfo.pImageIndices = &imageIndex;

        vkQueuePresentKHR(device.Queue(), &presentInfo);
        vkQueueWaitIdle(device.Queue());
    }
}
