#include <algorithm>
#include "RendererVulkan.hpp"
#include "ShaderVulkan.hpp"
#include "PipelineVulkan.hpp"

#include <vulkan\vulkan.h>
#include <GLFW/glfw3.h>

namespace
{
	VkQueue graphicsQueue;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	VkSemaphore vkSemaphore;
	std::vector<VkFramebuffer> swapChainFramebuffers;
}

namespace sx
{
	RendererVulkan::RendererVulkan(Window& window, const std::vector<uint32_t>& vertex, const std::vector<uint32_t>& fragment)
		: window(window)
	{
		//vkGetDeviceQueue(device, queueCreateInfoVector.queueFamilyIndex, 0, &graphicsQueue);

		//VkSurfaceCapabilitiesKHR surfaceCapabilities;
		//vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfaceCapabilities);

		//VkSurfaceFormatKHR format = { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

		//uint32_t presentModeCount;
		//vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);
		//std::vector<VkPresentModeKHR> presentModeVector(presentModeCount);
		//vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, presentModeVector.data());
		//if (std::find_if(presentModeVector.begin(), presentModeVector.end(), [](const VkPresentModeKHR& mode) {return mode == VK_PRESENT_MODE_MAILBOX_KHR; }) == presentModeVector.end())
		//	throw std::runtime_error("present_mode not available");

		//VkSwapchainCreateInfoKHR SwapchainInfo = {};
		//SwapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		//SwapchainInfo.surface = surface;
		//SwapchainInfo.minImageCount = surfaceCapabilities.minImageCount;
		//SwapchainInfo.imageFormat = format.format;
		//SwapchainInfo.imageColorSpace = format.colorSpace;
		//SwapchainInfo.imageExtent = surfaceCapabilities.currentExtent;
		//SwapchainInfo.imageArrayLayers = 1;
		//SwapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		//SwapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; //VK_SHARING_MODE_CONCURRENT
		//SwapchainInfo.preTransform = surfaceCapabilities.currentTransform;
		//SwapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		//SwapchainInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
		//SwapchainInfo.clipped = VK_TRUE;
		//SwapchainInfo.oldSwapchain = VK_NULL_HANDLE;

		//if (vkCreateSwapchainKHR(device, &SwapchainInfo, nullptr, &swapChain) != VK_SUCCESS)
		//	throw std::runtime_error("failed to create swap chain!");

		//uint32_t imageCount;
		//vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
		//swapChainImages.resize(imageCount);
		//vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

		//swapChainImageViews.resize(imageCount);

		//for (auto it = swapChainImageViews.begin(); it != swapChainImageViews.end(); it++)
		//{
		//	VkImageViewCreateInfo createInfo = {};
		//	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		//	createInfo.image = swapChainImages[std::distance(swapChainImageViews.begin(), it)];
		//	createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		//	createInfo.format = SwapchainInfo.imageFormat;
		//	createInfo.components = { VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY };
		//	createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		//	createInfo.subresourceRange.baseMipLevel = 0;
		//	createInfo.subresourceRange.levelCount = 1;
		//	createInfo.subresourceRange.baseArrayLayer = 0;
		//	createInfo.subresourceRange.layerCount = 1;

		//	if (vkCreateImageView(device, &createInfo, nullptr, &*it) != VK_SUCCESS) 
		//		throw std::runtime_error("failed to create image views!");
		//}
		//		
		//ShaderVertexVulkan vertexShader(device, vertex);
		//ShaderFragmentVulkan fragmentShader(device, fragment);
		//RenderPassVulkan renderPass(device, SwapchainInfo.imageFormat);
		//PipelineVulkan pipelineVulkan(device, renderPass, SwapchainInfo.imageExtent, vertexShader, fragmentShader);


		//swapChainFramebuffers.resize(swapChainImageViews.size());

		//for (size_t i = 0; i < swapChainImageViews.size(); i++) 
		//{
		//	VkFramebufferCreateInfo framebufferInfo = {};
		//	framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		//	framebufferInfo.renderPass = renderPass.RenderPass();
		//	framebufferInfo.attachmentCount = 1;
		//	framebufferInfo.pAttachments = &swapChainImageViews[i];
		//	framebufferInfo.width = SwapchainInfo.imageExtent.width;
		//	framebufferInfo.height = SwapchainInfo.imageExtent.height;
		//	framebufferInfo.layers = 1;

		//	if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS)
		//		throw std::runtime_error("failed to create framebuffer!");
		//}

		//VkCommandPoolCreateInfo poolInfo = {};
		//poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		//poolInfo.queueFamilyIndex = queueCreateInfoVector.queueFamilyIndex;

		//if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) 
		//	throw std::runtime_error("failed to create command pool!");

		//commandBuffers.resize(swapChainFramebuffers.size());

		//VkCommandBufferAllocateInfo allocInfo = {};
		//allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		//allocInfo.commandPool = commandPool;
		//allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		//allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

		//if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
		//	throw std::runtime_error("failed to allocate command buffers!");

		//for (size_t i = 0; i < commandBuffers.size(); i++) 
		//{
		//	VkCommandBufferBeginInfo beginInfo = {};
		//	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		//	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

		//	vkBeginCommandBuffer(commandBuffers[i], &beginInfo);

		//	VkRenderPassBeginInfo renderPassInfo = {};
		//	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		//	renderPassInfo.renderPass = renderPass.RenderPass();
		//	renderPassInfo.framebuffer = swapChainFramebuffers[i];
		//	renderPassInfo.renderArea.offset = { 0, 0 };
		//	renderPassInfo.renderArea.extent = SwapchainInfo.imageExtent;

		//	VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		//	renderPassInfo.clearValueCount = 1;
		//	renderPassInfo.pClearValues = &clearColor;

		//	vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		//	vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineVulkan.Pipeline());
		//	vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);
		//	vkCmdEndRenderPass(commandBuffers[i]);
		//	if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
		//		throw std::runtime_error("failed to record command buffer!");
		//}

		//VkSemaphoreCreateInfo semaphoreInfo = {};
		//semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		//if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &vkSemaphore) != VK_SUCCESS)
		//	throw std::runtime_error("failed to create semaphores!");
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
		/*uint32_t imageIndex;
		vkAcquireNextImageKHR(device, swapChain, std::numeric_limits<uint64_t>::max(), vkSemaphore, VK_NULL_HANDLE, &imageIndex);

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

		if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS)
			throw std::runtime_error("failed to submit draw command buffer!");

		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &vkSemaphore;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &swapChain;
		presentInfo.pImageIndices = &imageIndex;

		vkQueuePresentKHR(graphicsQueue, &presentInfo);

		vkQueueWaitIdle(graphicsQueue);
		vkDeviceWaitIdle(device);*/
	}
}

