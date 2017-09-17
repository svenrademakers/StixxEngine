#include "DeviceVulkan.hpp"
#include <algorithm>
#include <vector>

namespace sx
{
	DeviceVulkan::DeviceVulkan(InstanceVulkan& instance, SurfaceVulkan& surface)
	{
		const char* swapChainExtension = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
		VkDeviceQueueCreateInfo queueCreateInfoVector = CreateGraphicsQueue(instance.PhysicalDevice());
		queueFamily = queueCreateInfoVector.queueFamilyIndex;

		VkDeviceCreateInfo DeviceInfo = {};
		DeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		DeviceInfo.queueCreateInfoCount = 1;
		DeviceInfo.pQueueCreateInfos = &queueCreateInfoVector;
		DeviceInfo.pEnabledFeatures = nullptr;
		DeviceInfo.enabledExtensionCount = 1;
		DeviceInfo.ppEnabledExtensionNames = &swapChainExtension;
		if (vkCreateDevice(instance.PhysicalDevice(), &DeviceInfo, nullptr, &device) != VK_SUCCESS || device == nullptr)
			throw std::runtime_error("failed to find GPUs with Vulkan support!");

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(instance.PhysicalDevice(), queueFamily, surface.Surface(), &presentSupport);

		if (!presentSupport)
			throw std::runtime_error("deviceQueue family does not support present support");

		vkGetDeviceQueue(device, queueFamily, 0, &graphicsQueue);
	}

	DeviceVulkan::~DeviceVulkan()
	{
		vkDestroyDevice(device, nullptr);
	}

	const VkDevice& DeviceVulkan::Device()
	{
		return device;
	}

	uint32_t DeviceVulkan::QueueFamiliy()
	{
		return queueFamily;
	}

	const VkQueue& DeviceVulkan::Queue()
	{
		return graphicsQueue;
	}

	VkDeviceQueueCreateInfo DeviceVulkan::CreateGraphicsQueue(const VkPhysicalDevice& device) const
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

		float queuePriority = 1.0f;
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = static_cast<uint32_t>(std::distance(queueFamilies.begin(), graphicsQueue));
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		return queueCreateInfo;
	}

}