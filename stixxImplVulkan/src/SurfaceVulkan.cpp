#include "SurfaceVulkan.hpp"
#include <algorithm>

namespace sx
{
	SurfaceVulkan::SurfaceVulkan(InstanceVulkan& instance, GLFWwindow& window)
		: instance(instance)
	{
		if (glfwCreateWindowSurface(*instance, &window, nullptr, &handle) != VK_SUCCESS)
			throw std::runtime_error("failed to create window surface.");

		VkSurfaceCapabilitiesKHR surfaceCapabilities;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(instance.PhysicalDevice(), handle, &surfaceCapabilities);

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(instance.PhysicalDevice(), handle, &presentModeCount, nullptr);
		std::vector<VkPresentModeKHR> presentModeVector(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(instance.PhysicalDevice(), handle, &presentModeCount, presentModeVector.data());
		if (std::find_if(presentModeVector.begin(), presentModeVector.end(), [](const VkPresentModeKHR& mode) {return mode == VK_PRESENT_MODE_MAILBOX_KHR; }) == presentModeVector.end())
			throw std::runtime_error("present_mode not available");

		imageCount = surfaceCapabilities.minImageCount;
		extent = surfaceCapabilities.currentExtent;
		surfaceTransformFlagBitsKHR = surfaceCapabilities.currentTransform;
	}

	SurfaceVulkan::~SurfaceVulkan()
	{
		vkDestroySurfaceKHR(*instance, handle, nullptr);
	}

	const VkFormat SurfaceVulkan::Format()
	{
		return VK_FORMAT_B8G8R8A8_UNORM;
	}
	
	uint32_t SurfaceVulkan::ImageCount()
	{
		return imageCount;
	}

	VkExtent2D& SurfaceVulkan::Extent()
	{
		return extent;
	}

	VkColorSpaceKHR SurfaceVulkan::ColorSpace()
	{
		return VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	}

	VkSurfaceTransformFlagBitsKHR SurfaceVulkan::CurrentTransform()
	{
		return surfaceTransformFlagBitsKHR;
	}
}
