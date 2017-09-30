#ifndef DEVICE_MEMORY_ALLOCATOR_VULKAN_HPP
#define DEVICE_MEMORY_ALLOCATOR_VULKAN_HPP

#include <vector>
#include "vulkan/vulkan.h"

#define STAGING_BUFFER_SIZE 0x100000
#define MEMORY_CHUNK_SIZE 0x10000000

namespace sx
{
    class DeviceVulkan;
    class PhysicalDeviceVulkan;

    class DeviceMemoryAllocatorVulkan
    {
    public:
        DeviceMemoryAllocatorVulkan(DeviceVulkan& device, PhysicalDeviceVulkan& pdevice);
        virtual ~DeviceMemoryAllocatorVulkan();

        VkBuffer Load(const std::vector<uint32_t>& data);

    private:
        void CreateStatingBuffer();
        void AttachMemory(const VkBuffer& buffer, const size_t size);
        void AllocNextChunk(uint32_t memTypeBits);
        void CopyData2Device(const VkBuffer& buffer, const std::vector<uint32_t>& data) const;

        DeviceVulkan& device;
        PhysicalDeviceVulkan& pdevice;

        VkDeviceMemory stagingMemory;
        std::vector<std::pair<std::size_t, VkDeviceMemory>> memoryVector;
        VkBuffer stagingSrcBuffer;
        VkCommandBuffer commandBuffer;

        void* dataPtr;

    };
}

#endif