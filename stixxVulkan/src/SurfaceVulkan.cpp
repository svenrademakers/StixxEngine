#include "SurfaceVulkan.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "WindowGlfw.hpp"

namespace
{
	bool Supported(std::vector<vk::PresentModeKHR>& presentModes, vk::PresentModeKHR desired)
	{
		return (std::find_if(presentModes.begin(), presentModes.end(),
						 [desired](const vk::PresentModeKHR mode) {return mode == desired; }) != presentModes.end());
	}

	bool SupportsTripleBuffering(vk::SurfaceCapabilitiesKHR& surfaceCapabilities)
	{
		return (surfaceCapabilities.minImageCount < 3 && surfaceCapabilities.maxImageCount > 3);
	}


}
namespace sx
{
	SurfaceVulkan::~SurfaceVulkan()
	{
		vkDestroySurfaceKHR(instance, handle, nullptr);
	}

	void SurfaceVulkan::Init(vk::Instance& instance,vk::PhysicalDevice& pdevice, Window &window)
	{
        this->pdevice = pdevice;
        this->instance = instance;

		if (glfwCreateWindowSurface(instance, static_cast<GLFWwindow*>(window.GetHandle()), nullptr, &handle) != VK_SUCCESS)
			throw std::runtime_error("failed to create window surface.");

		auto surfaceCapabilities = pdevice.getSurfaceCapabilitiesKHR(handle);
		if (!SupportsTripleBuffering(surfaceCapabilities))
			throw std::runtime_error("surface not compatible with rendering strategy");

        auto surfaceFormats = pdevice.getSurfaceFormatsKHR(handle);

        if (surfaceFormats.size() == 1 && surfaceFormats[0].format == vk::Format::eUndefined)
            format.format = VK_FORMAT_B8G8R8A8_UNORM;
        else
            format.format = static_cast<VkFormat>(surfaceFormats[0].format);

        format.colorSpace = static_cast<VkColorSpaceKHR>(surfaceFormats[0].colorSpace);

        // Since all depth formats may be optional, we need to find a suitable depth format to use
        // Start with the highest precision packed format
        std::vector<vk::Format> depthFormats = {
                vk::Format::eD32SfloatS8Uint,
                vk::Format::eD32Sfloat,
                vk::Format::eD24UnormS8Uint,
                vk::Format::eD16UnormS8Uint,
                vk::Format::eD16Unorm
        };

        for (auto& format : depthFormats)
        {
            auto depthFormatProperties = pdevice.getFormatProperties(format);
            // Format must support depth stencil attachment for optimal tiling
            if (depthFormatProperties.optimalTilingFeatures & vk::FormatFeatureFlagBits::eDepthStencilAttachment)
            {
                surfaceDepthFormat = format;
                break;
            }
        }
		extent = surfaceCapabilities.currentExtent;
		currentTransform = static_cast<VkSurfaceTransformFlagBitsKHR>(surfaceCapabilities.currentTransform);
	}

    VkPresentModeKHR SurfaceVulkan::PresentMode()
    {
        auto presentModes = pdevice.getSurfacePresentModesKHR(handle);
        if (Supported(presentModes, vk::PresentModeKHR::eMailbox))
        {
            return static_cast<VkPresentModeKHR>(vk::PresentModeKHR::eMailbox);
        }
        return static_cast<VkPresentModeKHR>(vk::PresentModeKHR::eFifo);
    }

    uint32_t SurfaceVulkan::ImageCount()
    {
        return 3;
    }

    VkSurfaceFormatKHR SurfaceVulkan::Format()
    {
        return format;
    }

    VkExtent2D SurfaceVulkan::Extent()
    {
        return extent;
    }

    VkSurfaceTransformFlagBitsKHR SurfaceVulkan::CurrentTransform()
    {
        return currentTransform;
    }

}
