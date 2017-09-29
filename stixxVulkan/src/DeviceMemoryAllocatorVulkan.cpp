#include <algorithm>
#include "DeviceMemoryAllocatorVulkan.hpp"
#include "DeviceVulkan.hpp"
#include "PhysicalDeviceVulkan.hpp"

namespace sx
{
    DeviceMemoryAllocatorVulkan::DeviceMemoryAllocatorVulkan(const DeviceVulkan &device, const PhysicalDeviceVulkan &pdevice)
    {
        VkPhysicalDeviceMemoryProperties memoryProperties;
        vkGetPhysicalDeviceMemoryProperties(pdevice, &memoryProperties);

//        auto HostVisibleHeap = std::find_if(memoryProperties.memoryTypes,
//                                            memoryProperties.memoryTypes + memoryProperties.memoryTypeCount,
//                                            [](const VkMemoryType &memoryType) {
//
//                                            });
    }
}