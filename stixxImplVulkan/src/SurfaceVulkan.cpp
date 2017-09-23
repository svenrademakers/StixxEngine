#include "SurfaceVulkan.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>

//
//auto surfaceSize = vk::Extent2D(width, height);
//auto renderArea = vk::Rect2D(vk::Offset2D(), surfaceSize);
//auto viewport = vk::Viewport(0.0f, 0.0f, width, height, 0, 1.0f);
namespace sx
{
	SurfaceVulkan::~SurfaceVulkan()
	{
		vkDestroySurfaceKHR(instance, handle, nullptr);
	}

	void SurfaceVulkan::Init(vk::Instance& instance,vk::PhysicalDevice& pdevice, GLFWwindow &window)
	{
        this->instance = instance;
		if (glfwCreateWindowSurface(instance, &window, nullptr, &handle) != VK_SUCCESS)
			throw std::runtime_error("failed to create window surface.");

		auto surfaceCapabilities = pdevice.getSurfaceCapabilitiesKHR(handle);
		auto presentModes = pdevice.getSurfacePresentModesKHR(handle);

		for (auto presentMode : presentModes)
			std::cout <<"joh:" << static_cast<uint32_t>(presentMode);

		if (std::find_if(presentModes.begin(), presentModes.end(), [](const vk::PresentModeKHR mode) {return mode == vk::PresentModeKHR::eMailbox; }) == presentModes.end())
			throw std::runtime_error("present_mode not available");

		imageCount = surfaceCapabilities.minImageCount;
		extent = surfaceCapabilities.currentExtent;
		surfaceTransformFlagBitsKHR = static_cast<VkSurfaceTransformFlagBitsKHR>(surfaceCapabilities.currentTransform);
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
