#include <algorithm>
#include <Window.hpp>
#include <vulkan/vulkan.hpp>
#include <RendererVulkan.hpp>
#include <iostream>
#include "ShaderVulkan.hpp"

namespace
{
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;

	uint32_t QueueFamily(vk::PhysicalDevice device, vk::QueueFlags type)
	{
		auto devices = device.getQueueFamilyProperties();

		auto Queue = std::find_if(devices.begin(), devices.end(), [type](const vk::QueueFamilyProperties& properties) {
			return (properties.queueCount > 0) && (type & properties.queueFlags);
		});

		if (Queue == devices.end())
			throw std::runtime_error("cannot find queue family");

		return  static_cast<uint32_t>(std::distance(devices.begin(), Queue));
	}
}

namespace sx
{
	RendererVulkan::RendererVulkan(sx::WindowGlfw& window, const std::vector<uint32_t>& vertex, const std::vector<uint32_t>& fragment)
	{
        auto appInfo = vk::ApplicationInfo(
                window.Name(),
                VK_MAKE_VERSION(1, 0, 0),
                "Stixx",
                VK_MAKE_VERSION(1, 0, 0),
                VK_API_VERSION_1_0
        );

        auto instance = vk::createInstance(
                vk::InstanceCreateInfo(
                        vk::InstanceCreateFlags(),
                        &appInfo,
                        0,
                        nullptr,
                        window.InstanceExtensions().size(),
                        window.InstanceExtensions().data()
                )
        );

        pdevice = instance.enumeratePhysicalDevices()[0];
        auto gpuFeatures = pdevice.getFeatures();
        auto gpuQueueProps = pdevice.getQueueFamilyProperties();
        uint32_t graphicsFamilyIndex = QueueFamily(pdevice, vk::QueueFlagBits::eGraphics);

        float priority = 1.0;
        auto queueCreateInfos = std::vector<vk::DeviceQueueCreateInfo>();

        queueCreateInfos.push_back(
                vk::DeviceQueueCreateInfo(
                        vk::DeviceQueueCreateFlags(),
                        graphicsFamilyIndex,
                        1,
                        &priority
                )
        );

        const char * deviceExtension = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

        device = pdevice.createDevice(
                vk::DeviceCreateInfo(
                        vk::DeviceCreateFlags(),
                        queueCreateInfos.size(),
                        queueCreateInfos.data(),
                        0,
                        nullptr,
                        1,
                        &deviceExtension,
                        &gpuFeatures
                )
        );

        surface.Init(instance, pdevice, *window.GetHandle());
        swapchain.Init(device, surface);
        renderPass.Init(device, swapchain);

        vk::Viewport viewport(0.0f, 0.0f,
                              static_cast<float>(window.Size().first),
                              static_cast<float>(window.Size().second),
                              0.0f, 1.0f);

        ShaderVertexVulkan vertexShader(device, vertex);
        ShaderFragmentVulkan fragmentShader(device, fragment);
		pipeline.Init(device, renderPass, surface, vertexShader, fragmentShader, viewport);

		commandPool = device.createCommandPool(vk::CommandPoolCreateInfo(
			vk::CommandPoolCreateFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer),	
			graphicsFamilyIndex), nullptr);
		
		commandBuffers = device.allocateCommandBuffers(
			vk::CommandBufferAllocateInfo(
				commandPool,
				vk::CommandBufferLevel::ePrimary,
				swapchain.ImageViews().size()
			)
		);

		graphicsQueue = device.getQueue(graphicsFamilyIndex, 0);

		for (size_t i = 0; i < commandBuffers.size(); i++) 
		{
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

			vkBeginCommandBuffer(commandBuffers[i], &beginInfo);

			VkRenderPassBeginInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = *renderPass;
			renderPassInfo.framebuffer = renderPass.FrameBuffers()[i];
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = swapchain.Extent();

			VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &clearColor;

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, *pipeline);
			vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);
			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
				throw std::runtime_error("failed to record command buffer!");
		}

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
		vkDestroyCommandPool(device, commandPool, nullptr);
    }

	void RendererVulkan::Draw()
	{
			uint32_t imageIndex;
			vkAcquireNextImageKHR(device, *swapchain, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

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

			vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);

			VkPresentInfoKHR presentInfo = {};
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.waitSemaphoreCount = 1;
			presentInfo.pWaitSemaphores = &renderFinishedSemaphore;
			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = &*swapchain;
			presentInfo.pImageIndices = &imageIndex;

			vkQueuePresentKHR(graphicsQueue, &presentInfo);
			vkQueueWaitIdle(graphicsQueue);
	}
}

