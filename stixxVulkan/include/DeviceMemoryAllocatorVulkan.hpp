#ifndef DEVICE_MEMORY_ALLOCATOR_VULKAN_HPP
#define DEVICE_MEMORY_ALLOCATOR_VULKAN_HPP

#include <vector>
#include "vulkan/vulkan.h"

namespace sx
{
    class DeviceVulkan;
    class PhysicalDeviceVulkan;

    class DeviceMemoryAllocatorVulkan
    {
    public:
        DeviceMemoryAllocatorVulkan(const DeviceVulkan& device, const PhysicalDeviceVulkan& pdevice);

    private:
        std::vector<VkDeviceMemory> memoryVector;
    };
}

#endif