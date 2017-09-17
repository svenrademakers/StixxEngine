#include <algorithm>
#include "RendererVulkan.hpp"
#include "PipelineVulkan.hpp"

#include <vulkan\vulkan.h>
#include <GLFW/glfw3.h>

namespace
{
	VkCommandPool commandPool;
	VkSemaphore vkSemaphore;
	std::vector<VkCommandBuffer> commandBuffers;
}

namespace sx
{
	RendererVulkan::RendererVulkan(DeviceVulkan& device, PipelineVulkan& pipeline, RenderPassVulkan& renderPass, SwapchainVulkan& swapchain)
		: device(device)
		, pipeline(pipeline)
		, swapchain(swapchain)
	{
		VkCommandPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = device.QueueFamiliy();

		if (vkCreateCommandPool(device.Device(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS) 
			throw std::runtime_error("failed to create command pool!");

		commandBuffers.resize(swapchain.ImageViews().size());

		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

		if (vkAllocateCommandBuffers(device.Device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate command buffers!");

		for (size_t i = 0; i < commandBuffers.size(); i++) 
		{
			VkCommandBufferBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

			vkBeginCommandBuffer(commandBuffers[i], &beginInfo);

			VkRenderPassBeginInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = renderPass.RenderPass();
			renderPassInfo.framebuffer = renderPass.FrameBuffers()[i];
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = swapchain.Extent();

			VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &clearColor;

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.Pipeline());
			vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);
			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
				throw std::runtime_error("failed to record command buffer!");
		}

		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		if (vkCreateSemaphore(device.Device(), &semaphoreInfo, nullptr, &vkSemaphore) != VK_SUCCESS)
			throw std::runtime_error("failed to create semaphores!");
	}

	RendererVulkan::~RendererVulkan()
	{
		//vkDestroyCommandPool(device, commandPool, nullptr);

		//for (size_t i = 0; i < swapChainFramebuffers.size(); i++) 
		//{
		//	vkDestroyFramebuffer(device, swapChainFramebuffers[i], nullptr);
		//}

		//for (size_t i = 0; i < swapChainImageViews.size(); i++) 
		//{
		//	vkDestroyImageView(device, swapChainImageViews[i], nullptr);
		//}

		//vkDestroySwapchainKHR(device, swapChain, nullptr);
		//vkDestroyDevice(device, nullptr);
		//vkDestroySurfaceKHR(instance, surface, nullptr);
	}
	


	void RendererVulkan::Draw()
	{
		uint32_t imageIndex;
		vkAcquireNextImageKHR(device.Device(), swapchain.Swapchain(), std::numeric_limits<uint64_t>::max(), vkSemaphore, VK_NULL_HANDLE, &imageIndex);

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkPipelineStageFlags waitStages = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &vkSemaphore;
		submitInfo.pWaitDstStageMask = &waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffers[imageIndex];
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &vkSemaphore;

		if (vkQueueSubmit(device.Queue(), 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS)
			throw std::runtime_error("failed to submit draw command buffer!");

		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &vkSemaphore;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &swapchain.Swapchain();
		presentInfo.pImageIndices = &imageIndex;

		vkQueuePresentKHR(device.Queue(), &presentInfo);
		vkQueueWaitIdle(device.Queue());
		vkDeviceWaitIdle(device.Device());
	}
}

