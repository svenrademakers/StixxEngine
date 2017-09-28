#include "DeviceMemoryVulkan.hpp"
#include <stdexcept>

namespace sx
{
    DeviceMemoryVulkan::DeviceMemoryVulkan(const VkDevice& device, const VkPhysicalDevice& pdevice)
        : device(device)
        , pdevice(pdevice)
    {}

    std::vector<DeviceMemory::Heap> DeviceMemoryVulkan::HeapInfo()
    {
        std::vector<DeviceMemory::Heap> heaps;
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(pdevice, &memProperties);

        for(int i = 0; i < memProperties.memoryHeapCount; ++i)
        {
            auto heapProperties = memProperties.memoryHeaps[i];
            heaps.push_back({heapProperties.size, heapProperties.flags == VK_MEMORY_HEAP_DEVICE_LOCAL_BIT});
        }
        
        for (int i = 0; i < memProperties.memoryTypeCount; ++i)
        {
            auto memoryTypes = memProperties.memoryTypes[i];
            heaps[memoryTypes.heapIndex].supportedTypes |= memoryTypes.propertyFlags;             
        }
    }

    bool DeviceMemoryVulkan::AllocateMemory(uint8_t heapId, std::size_t size)
    {
        return false;
    }
}