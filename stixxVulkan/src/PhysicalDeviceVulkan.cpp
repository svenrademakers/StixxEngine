#include "PhysicalDeviceVulkan.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace sx
{
    PhysicalDeviceVulkan::PhysicalDeviceVulkan(const VkInstance &instance)
    {
        uint32_t deviceCount = 1;
        vkEnumeratePhysicalDevices(instance, &deviceCount, &handle);
    }

    PhysicalDeviceVulkan::~PhysicalDeviceVulkan()
    {}

    bool PhysicalDeviceVulkan::PresentSupport(const VkSurfaceKHR &surface)
    {
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(handle, QueueIndex(VK_QUEUE_GRAPHICS_BIT), surface, &presentSupport);
        return presentSupport;
    }

    uint32_t PhysicalDeviceVulkan::QueueIndex(const VkQueueFlagBits bits)
    {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(handle, &queueFamilyCount, nullptr);
        std::vector <VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(handle, &queueFamilyCount, queueFamilies.data());

        auto graphicsQueue = std::find_if(queueFamilies.begin(), queueFamilies.end(),
                                          [bits](const VkQueueFamilyProperties &properties) {
                                              return (properties.queueCount > 0) &&
                                                     (properties.queueFlags & bits);
                                          });

        if (graphicsQueue == queueFamilies.end())
            throw std::runtime_error("cannot find queue family.");

        return static_cast<uint32_t>(std::distance(queueFamilies.begin(), graphicsQueue));
    }

    uint32_t PhysicalDeviceVulkan::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
    {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(handle, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }
}