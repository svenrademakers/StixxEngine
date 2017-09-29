#include "DeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include <stdexcept>
#include <algorithm>

namespace sx
{
	DeviceVulkan::DeviceVulkan(PhysicalDeviceVulkan& pdevice)
		: pdevice(pdevice)
	{
		float queuePriority = 1.0f;
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = pdevice.QueueIndex(VK_QUEUE_GRAPHICS_BIT);
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

	}

	DeviceVulkan::~DeviceVulkan()
	{
		vkDestroyDevice(handle, nullptr);
	}

	const VkQueue DeviceVulkan::Queue()
	{
		return queue;
	}
}
