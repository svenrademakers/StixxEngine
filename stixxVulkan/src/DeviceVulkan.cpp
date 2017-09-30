#include "DeviceVulkan.hpp"
#include "PhysicalDeviceVulkan.hpp"
#include <stdexcept>
#include <algorithm>

namespace sx
{
	DeviceVulkan::DeviceVulkan(PhysicalDeviceVulkan& pdevice)
		: pdevice(pdevice)
	{
		uint32_t queueIndex = pdevice.QueueIndex(static_cast<VkQueueFlagBits>(VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_TRANSFER_BIT));

		float queuePriority = 1.0f;
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueIndex;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures = {};
		vkGetPhysicalDeviceFeatures(pdevice, &deviceFeatures);

		std::vector<const char*> enableExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		
		VkDeviceCreateInfo DeviceInfo = {};
		DeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		DeviceInfo.queueCreateInfoCount = 1;
		DeviceInfo.pQueueCreateInfos = &queueCreateInfo;
		DeviceInfo.enabledExtensionCount = 1;
		DeviceInfo.ppEnabledExtensionNames = enableExtensions.data();
		DeviceInfo.pEnabledFeatures = nullptr;

		if (vkCreateDevice(pdevice, &DeviceInfo, nullptr, &handle) != VK_SUCCESS)
			throw std::runtime_error("failed to find GPUs with Vulkan support!");

		vkGetDeviceQueue(handle, queueIndex, 0, &queue);

		VkCommandPoolCreateInfo commandPoolCreateInfo = {};
		commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		commandPoolCreateInfo.queueFamilyIndex = queueIndex;
		vkCreateCommandPool(handle, &commandPoolCreateInfo, nullptr, &commandPool);
	}

	DeviceVulkan::~DeviceVulkan()
	{
		vkDestroyCommandPool(handle, commandPool, nullptr);
		vkDestroyDevice(handle, nullptr);
	}

	const VkQueue& DeviceVulkan::Queue()
	{
		return queue;
	}

	const VkCommandPool& DeviceVulkan::CommandPool()
	{
		return commandPool;
	}
}
