#ifndef DEVICE_MEMORY_ALLOCATOR_VULKAN_HPP
#define DEVICE_MEMORY_ALLOCATOR_VULKAN_HPP

#include <vector>
#include "vulkan/vulkan.h"

#define STAGING_BUFFER_SIZE (0x10000000)

namespace sx
{
    class DeviceVulkan;
    class PhysicalDeviceVulkan;

    class DeviceMemoryAllocatorVulkan
    {
    public:
        DeviceMemoryAllocatorVulkan(const DeviceVulkan& device, PhysicalDeviceVulkan& pdevice);
        virtual ~DeviceMemoryAllocatorVulkan();

    private:
        const DeviceVulkan& device;
        const PhysicalDeviceVulkan& pdevice;

        std::vector<VkDeviceMemory> memoryVector;
        VkBuffer stagingBuffer;
        uint32_t stagingBufferAlignment;
    };
}

#endif