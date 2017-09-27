#include "DeviceMemoryVulkan.hpp"
#include <stdexcept>

namespace sx
{
    DeviceMemoryVulkan::DeviceMemoryVulkan(const VkDevice device, const VkPhysicalDevice pdevice)
        : device(device)
        , pdevice(pdevice)
    {}

    std::vector<Heap> DeviceMemoryVulkan::Heaps()
    {
        std::vector<Heap> heaps;

        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(pdevice, &memProperties);

        for(int i= 0; i < memProperties.memoryHeapCount; ++i)
        {
            //memProperties.memoryTypes[i]
            //heaps.push_back({});
        }


       // throw std::runtime_error("failed to find suitable memory type!");
        return heaps;
    }

    bool DeviceMemoryVulkan::AllocateMemory(std::size_t size)
    {
        return false;
    }
}