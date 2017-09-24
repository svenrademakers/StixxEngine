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
    uint32_t memorySize;
    uint32_t indicesSize;

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


	uint32_t MemoryType(vk::PhysicalDevice& physicalDevice, uint32_t typeBits, vk::MemoryPropertyFlags properties)
	{
        vk::PhysicalDeviceMemoryProperties memoryProperties;
        physicalDevice.getMemoryProperties(&memoryProperties);

		for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
		{
			if ((typeBits & 1) == 1)
			{
				if ((memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
				{
					return i;
				}
			}
			typeBits >>= 1;
		}
	};
}

namespace sx
{
	RendererVulkan::RendererVulkan(sx::Window& window, const std::vector<uint32_t>& vertex, const std::vector<uint32_t>& fragment)
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
        uint32_t graphicsFamilyIndex = QueueFamily(pdevice, vk::QueueFlagBits::eGraphics);

        float priority = 1.0;
		std::array<VkDeviceQueueCreateInfo,1> queueInfos = {};
		queueInfos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueInfos[0].queueCount = 1;
		queueInfos[0].pQueuePriorities = &priority;
		queueInfos[0].queueFamilyIndex = graphicsFamilyIndex;

        std::array<const char *,1> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.pQueueCreateInfos = queueInfos.data();
		deviceCreateInfo.queueCreateInfoCount = queueInfos.size();
		deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
		deviceCreateInfo.enabledExtensionCount = deviceExtensions.size();
		VkPhysicalDeviceFeatures features = gpuFeatures;
		deviceCreateInfo.pEnabledFeatures = &features;

        device = pdevice.createDevice(deviceCreateInfo);

        surface.Init(instance, pdevice, window);
        swapchain.Init(device, surface);
        renderPass.Init(device, swapchain, surface);

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
		//vkDestroyDevice(device, nullptr);
		vkDestroyInstance(instance, nullptr);
    }

    void RendererVulkan::LoadScene(const std::vector<sx::Vertex>& vertices, const std::vector<uint32_t>& indices)
	{
        VkDevice dev = device;
        indicesSize = (indices.size() * sizeof(uint32_t));
        memorySize = (vertices.size() * sizeof(sx::Vertex));

        VkBuffer buffer;
        VkBufferCreateInfo createVertexBuffer = {};
        createVertexBuffer.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        createVertexBuffer.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        createVertexBuffer.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createVertexBuffer.size = memorySize;
        vkCreateBuffer(device, &createVertexBuffer, nullptr, &buffer);
        buffers.push_back(buffer);

        VkBuffer IndicesBuffer;
        VkBufferCreateInfo createIndicesBuffer = {};
        createIndicesBuffer.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        createIndicesBuffer.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        createIndicesBuffer.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createIndicesBuffer.size = indicesSize;
        vkCreateBuffer(device, &createIndicesBuffer, nullptr, &IndicesBuffer);
        buffers.push_back(IndicesBuffer);

        auto memRequirements = device.getBufferMemoryRequirements(buffer);
        auto memRequirements2 = device.getBufferMemoryRequirements(IndicesBuffer);


        VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = MemoryType(pdevice, memRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
        auto memory = device.allocateMemory(allocInfo, nullptr);


        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements2.size;
        allocInfo.memoryTypeIndex = MemoryType(pdevice, memRequirements2.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
        auto memory2 = device.allocateMemory(allocInfo, nullptr);

        device.bindBufferMemory(buffers[0], memory, 0);
        device.bindBufferMemory(buffers[1], memory2, 0);

        void* data;
		vkMapMemory(device, memory, 0, allocInfo.allocationSize, 0, &data);
		memcpy(data, vertices.data(), memorySize);
        vkUnmapMemory(device, memory);

        data= nullptr;
        vkMapMemory(device, memory2, 0, allocInfo.allocationSize, 0, &data);
        memcpy(data, indices.data(), indicesSize);
        vkUnmapMemory(device, memory2);


        LoadDrawingCommands();
	}

    void RendererVulkan::LoadDrawingCommands()
    {
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
            renderPassInfo.renderArea.extent = surface.Extent();

            VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
            renderPassInfo.clearValueCount = 1;
            renderPassInfo.pClearValues = &clearColor;

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
            vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, *pipeline);

            VkBuffer vertexBuffers[] = {buffers[0]};
            VkDeviceSize offsets[] = {0};
            vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
            vkCmdBindIndexBuffer(commandBuffers[i], buffers[1], 0, VK_INDEX_TYPE_UINT32);
            vkCmdDrawIndexed(commandBuffers[i], 6, 1, 0, 0, 0);

            vkCmdEndRenderPass(commandBuffers[i]);
            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
                throw std::runtime_error("failed to record command buffer!");
        }
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

