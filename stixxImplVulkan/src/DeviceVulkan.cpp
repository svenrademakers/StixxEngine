#include "DeviceVulkan.hpp"
#include <algorithm>
#include <vector>
#include<stdexcept>

namespace sx
{
	DeviceVulkan::DeviceVulkan(InstanceVulkan& instance, SurfaceVulkan& surface)
	{
		queueFamilyIndex = GetGraphicsFamilyIndex(instance.PhysicalDevice());

		float queuePriority = 1.0f;
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures = {};
		vkGetPhysicalDeviceFeatures(instance.PhysicalDevice(), &deviceFeatures);

		std::vector<const char*> enableExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		
		VkDeviceCreateInfo DeviceInfo = {};
		DeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		DeviceInfo.queueCreateInfoCount = 1;
		DeviceInfo.pQueueCreateInfos = &queueCreateInfo;
		DeviceInfo.enabledExtensionCount = 1;
		DeviceInfo.ppEnabledExtensionNames = enableExtensions.data();
		DeviceInfo.pEnabledFeatures = nullptr;

		if (vkCreateDevice(instance.PhysicalDevice(), &DeviceInfo, nullptr, &handle) != VK_SUCCESS)
			throw std::runtime_error("failed to find GPUs with Vulkan support!");

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(instance.PhysicalDevice(), queueFamilyIndex, *surface, &presentSupport);

		if (!presentSupport)
			throw std::runtime_error("deviceQueue family does not support present support");
	}

	DeviceVulkan::~DeviceVulkan()
	{
		vkDestroyDevice(handle, nullptr);
	}

	uint32_t DeviceVulkan::GetGraphicsFamilyIndex(const VkPhysicalDevice& device) const
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		auto graphicsQueue = std::find_if(queueFamilies.begin(), queueFamilies.end(), [](const VkQueueFamilyProperties& properties) {
			return (properties.queueCount > 0) && (properties.queueFlags & VK_QUEUE_GRAPHICS_BIT);
		});

		if (graphicsQueue == queueFamilies.end())
			throw std::runtime_error("cannot find Graphics queue family.");

		return static_cast<uint32_t>(std::distance(queueFamilies.begin(), graphicsQueue));
	}
}
