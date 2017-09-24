#include "SurfaceVulkan.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>

//
//auto surfaceSize = vk::Extent2D(width, height);
//auto renderArea = vk::Rect2D(vk::Offset2D(), surfaceSize);
//auto viewport = vk::Viewport(0.0f, 0.0f, width, height, 0, 1.0f);

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

	void SurfaceVulkan::Init(vk::Instance& instance,vk::PhysicalDevice& pdevice, GLFWwindow &window)
	{
        this->pdevice = pdevice;
        this->instance = instance;

		if (glfwCreateWindowSurface(instance, &window, nullptr, &handle) != VK_SUCCESS)
			throw std::runtime_error("failed to create window surface.");

		auto surfaceCapabilities = pdevice.getSurfaceCapabilitiesKHR(handle);
		if (!SupportsTripleBuffering(surfaceCapabilities))
			throw std::runtime_error("surface not compatible with rendering strategy");

        auto surfaceFormats = pdevice.getSurfaceFormatsKHR(handle);

        if (surfaceFormats.size() == 1 && surfaceFormats[0].format == vk::Format::eUndefined)
            surfaceColorFormat = vk::Format::eB8G8R8A8Unorm;
        else
            surfaceColorFormat = surfaceFormats[0].format;

        surfaceColorSpace = surfaceFormats[0].colorSpace;
        auto formatProperties = pdevice.getFormatProperties(vk::Format::eR8G8B8A8Unorm);

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
		surfaceTransformFlagBitsKHR = static_cast<VkSurfaceTransformFlagBitsKHR>(surfaceCapabilities.currentTransform);
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
}
