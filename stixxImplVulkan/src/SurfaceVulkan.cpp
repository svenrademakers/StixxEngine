#include "SurfaceVulkan.hpp"
#include <algorithm>

namespace sx
{
	SurfaceVulkan::SurfaceVulkan(InstanceVulkan& instance, GLFWwindow& window)
	{
		if (glfwCreateWindowSurface(instance.Instance(), &window, nullptr, &surface) != VK_SUCCESS)
			throw std::runtime_error("failed to create window surface.");

		VkSurfaceCapabilitiesKHR surfaceCapabilities;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(instance.PhysicalDevice(), surface, &surfaceCapabilities);

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(instance.PhysicalDevice(), surface, &presentModeCount, nullptr);
		std::vector<VkPresentModeKHR> presentModeVector(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(instance.PhysicalDevice(), surface, &presentModeCount, presentModeVector.data());
		if (std::find_if(presentModeVector.begin(), presentModeVector.end(), [](const VkPresentModeKHR& mode) {return mode == VK_PRESENT_MODE_MAILBOX_KHR; }) == presentModeVector.end())
			throw std::runtime_error("present_mode not available");
	}

	const VkSurfaceKHR& SurfaceVulkan::Surface()
	{
		return surface;
	}

	const VkSurfaceFormatKHR SurfaceVulkan::Format()
	{
		return { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}
}
