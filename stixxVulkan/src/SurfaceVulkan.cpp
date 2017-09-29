#include "SurfaceVulkan.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "WindowGlfw.hpp"
#include "InstanceVulkan.hpp"
#include "DeviceVulkan.hpp"
#include "Window.hpp"

namespace sx
{
	SurfaceVulkan::SurfaceVulkan(const VkInstance& instance, const VkPhysicalDevice& pdevice)
        : instance(instance)
        , pdevice(pdevice)
    {}

    SurfaceVulkan::~SurfaceVulkan()
    {
        vkDestroySurfaceKHR(instance, surface, nullptr);
    }

    SurfaceVulkan::operator const VkSurfaceKHR&() const
    {
        return surface;
    }

    bool SurfaceVulkan::CreateSurface(Window& window)
    {
        if (glfwCreateWindowSurface(instance, static_cast<GLFWwindow*>(window.GetHandle()), nullptr, &surface) == VK_SUCCESS)
        {
            VkSurfaceCapabilitiesKHR surfaceCapabilities;
            vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pdevice, surface, &surfaceCapabilities);

            extent.width = surfaceCapabilities.currentExtent.width;
            extent.height = surfaceCapabilities.currentExtent.height;

            currentTransform = static_cast<Surface::Transform>(surfaceCapabilities.currentTransform);
            imageCountMax = surfaceCapabilities.maxImageCount;
            return true;
        }

        return false;
    }

    uint32_t SurfaceVulkan::MaxImageCount()
    {
        return imageCountMax;
    }

    bool SurfaceVulkan::isSupported(const PresentMode type)
    {
        uint32_t count;
        vkGetPhysicalDeviceSurfacePresentModesKHR(pdevice, surface, &count,nullptr);
        std::vector<VkPresentModeKHR> presentModes(count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(pdevice, surface, &count,presentModes.data());

        return (std::find_if(presentModes.begin(), presentModes.end(),
                             [type](const VkPresentModeKHR& mode) { return mode == static_cast<VkPresentModeKHR>(type); }) != presentModes.end());
    }

    Surface::SurfaceFormat SurfaceVulkan::Format()
    {
        Surface::SurfaceFormat format;

        uint32_t count = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(pdevice, surface, &count, nullptr );
        std::vector<VkSurfaceFormatKHR> surfaceFormats(count);
        vkGetPhysicalDeviceSurfaceFormatsKHR(pdevice, surface, &count, surfaceFormats.data());

        if (surfaceFormats.size() == 1 && surfaceFormats[0].format == VK_FORMAT_UNDEFINED)
            format.first = static_cast<Surface::ColorFormat>(VK_FORMAT_B8G8R8A8_UNORM);
        else
            format.first = static_cast<Surface::ColorFormat>(surfaceFormats[0].format);

        format.second = static_cast<Surface::ColorSpace>(surfaceFormats[0].colorSpace);

        return format;
    }

    Surface::Extent SurfaceVulkan::CurrentExtent()
    {
        return extent;
    }

    Surface::Transform SurfaceVulkan::CurrentTransform()
    {
        return currentTransform;
    }
}
