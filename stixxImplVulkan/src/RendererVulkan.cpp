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
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = window.Name();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "stixx";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo InstanceInfo = {};
        InstanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        InstanceInfo.pApplicationInfo = &appInfo;
        InstanceInfo.enabledExtensionCount = static_cast<uint32_t>(window.InstanceExtensions().size());
        InstanceInfo.ppEnabledExtensionNames = window.InstanceExtensions().data();
        InstanceInfo.enabledLayerCount = 0;

        instance = vk::createInstance(InstanceInfo);
        pdevice = instance.enumeratePhysicalDevices()[0];

        surface.Init(instance, pdevice, *window.GetHandle());
        swapchain.Init(device, surface);
        renderPass.Init(device, swapchain);
		ShaderVertexVulkan vertexShader(device, vertex);
		ShaderFragmentVulkan fragmentShader(device, fragment);

		pipeline.Init(device, renderPass, surface, vertexShader, fragmentShader);

		uint32_t graphicsFamilyIndex = QueueFamily(pdevice, vk::QueueFlagBits::eGraphics);
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

			if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS)
				throw std::runtime_error("failed to submit draw command buffer!");

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

