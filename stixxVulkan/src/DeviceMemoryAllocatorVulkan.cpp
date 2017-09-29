#include <algorithm>
#include <stdexcept>
#include "DeviceMemoryAllocatorVulkan.hpp"
#include "DeviceVulkan.hpp"
#include "PhysicalDeviceVulkan.hpp"

namespace sx
{
    DeviceMemoryAllocatorVulkan::DeviceMemoryAllocatorVulkan(const DeviceVulkan &device, PhysicalDeviceVulkan &pdevice)
        : device(device)
        , pdevice(pdevice)
    {
        VkBufferCreateInfo stagingBufferInfo = {};
        stagingBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        stagingBufferInfo.size = STAGING_BUFFER_SIZE;
        stagingBufferInfo.flags = 0;
        stagingBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        stagingBufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        stagingBufferInfo.queueFamilyIndexCount = 0;
        stagingBufferInfo.pQueueFamilyIndices = 0;
        vkCreateBuffer(device,&stagingBufferInfo, nullptr,  &stagingBuffer);

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, stagingBuffer, &memRequirements);

        VkDeviceMemory stagingMemory;
        VkMemoryAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = pdevice.FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        vkAllocateMemory(device, &allocInfo, nullptr, &stagingMemory);
        memoryVector.push_back(stagingMemory);
    }

    DeviceMemoryAllocatorVulkan::~DeviceMemoryAllocatorVulkan()
    {
        vkDestroyBuffer(device, stagingBuffer, nullptr);

        for (auto mem : memoryVector)
        {
            vkFreeMemory(device, mem, nullptr);
        }
    }

}