#ifndef PHYSICAL_DEVICE_VULKAN_HPP
#define PHYSICAL_DEVICE_VULKAN_HPP

#include "vulkan/vulkan.h"
#include "utils/CastOperator.hpp"

namespace sx
{
    class PhysicalDeviceVulkan
            : public CastOperator<VkPhysicalDevice>
    {
    public:
        PhysicalDeviceVulkan(const VkInstance& instance);
        virtual ~PhysicalDeviceVulkan();

        bool PresentSupport(const VkSurfaceKHR& surface);

        uint32_t QueueIndex(const VkQueueFlagBits bits);
    };
}
#endif
