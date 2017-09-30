#include <algorithm>
#include <stdexcept>
#include <cstring>
#include "DeviceMemoryAllocatorVulkan.hpp"
#include "DeviceVulkan.hpp"
#include "PhysicalDeviceVulkan.hpp"

namespace sx
{
    DeviceMemoryAllocatorVulkan::DeviceMemoryAllocatorVulkan(DeviceVulkan &device, PhysicalDeviceVulkan &pdevice)
        : device(device)
        , pdevice(pdevice)
    {
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = device.CommandPool();
        allocInfo.commandBufferCount = 1;
        vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

        CreateStatingBuffer();
    }

    DeviceMemoryAllocatorVulkan::~DeviceMemoryAllocatorVulkan()
    {
        vkFreeCommandBuffers(device, device.CommandPool(), 1, &commandBuffer);

        vkDestroyBuffer(device, stagingSrcBuffer, nullptr);

        vkUnmapMemory(device, stagingMemory);
        vkFreeMemory(device, stagingMemory, nullptr);

        for (auto mem : memoryVector)
            vkFreeMemory(device, mem.second, nullptr);
    }

    void DeviceMemoryAllocatorVulkan::CreateStatingBuffer()
    {
        VkBufferCreateInfo stagingBufferInfo = {};
        stagingBufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        stagingBufferInfo.size = STAGING_BUFFER_SIZE;
        stagingBufferInfo.flags = 0;
        stagingBufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        stagingBufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        stagingBufferInfo.queueFamilyIndexCount = 0;
        stagingBufferInfo.pQueueFamilyIndices = 0;
        vkCreateBuffer(device, &stagingBufferInfo, nullptr,  &stagingSrcBuffer);

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, stagingSrcBuffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = pdevice.FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        vkAllocateMemory(device, &allocInfo, nullptr, &stagingMemory);

        vkBindBufferMemory(device, stagingSrcBuffer, stagingMemory, 0);

        vkMapMemory(device, stagingMemory, 0, VK_WHOLE_SIZE, 0, &dataPtr);
    }

    VkBuffer DeviceMemoryAllocatorVulkan::Load(const std::vector<uint32_t>& data)
    {
        if (data.size() > STAGING_BUFFER_SIZE)
            std::runtime_error("cannot allocate this big piece of memory");

        VkBuffer  buffer;
        VkBufferCreateInfo bufferInfo = {};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = data.size();
        bufferInfo.flags = 0;
        bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT |  VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        bufferInfo.queueFamilyIndexCount = 0;
        bufferInfo.pQueueFamilyIndices = 0;
        vkCreateBuffer(device, &bufferInfo, nullptr,  &buffer);

        AttachMemory(buffer, data.size());

        CopyData2Device(buffer, data);

        return buffer;
    }

    void DeviceMemoryAllocatorVulkan::AttachMemory(const VkBuffer& buffer, const std::size_t size)
    {
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

        if (memoryVector.empty() || (size > (MEMORY_CHUNK_SIZE - memoryVector.back().first)))
            AllocNextChunk(memRequirements.memoryTypeBits);

        vkBindBufferMemory(device, buffer, memoryVector.back().second, memoryVector.back().first);
        memoryVector.back().first += memRequirements.size;
    }

    void DeviceMemoryAllocatorVulkan::AllocNextChunk(uint32_t memTypeBits)
    {
        VkDeviceMemory memChunk;
        VkMemoryAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = MEMORY_CHUNK_SIZE;
        allocInfo.memoryTypeIndex = pdevice.FindMemoryType(memTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        vkAllocateMemory(device, &allocInfo, nullptr, &memChunk);
        memoryVector.push_back({0, memChunk});
    }

    void DeviceMemoryAllocatorVulkan::CopyData2Device(const VkBuffer& buffer, const std::vector<uint32_t>& data) const
    {
        std::copy(data.begin(), data.end(), static_cast<uint32_t*>(dataPtr));

        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        VkBufferCopy copyRegion = {};
        copyRegion.size = data.size();
        vkCmdCopyBuffer(commandBuffer, stagingSrcBuffer, buffer, 1, &copyRegion);

        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(device.Queue(), 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(device.Queue());

        vkResetCommandBuffer(commandBuffer, 0);
    }


}