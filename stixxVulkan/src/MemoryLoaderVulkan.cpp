#include "MemoryLoaderVulkan.hpp"

namespace
{
	uint32_t FindMemoryType(const VkPhysicalDevice device, uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(device, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		throw std::runtime_error("failed to find suitable memory type!");
	}
}

namespace sx
{
	MemoryLoaderVulkan::MemoryLoaderVulkan(const VkDevice& device, const VkPhysicalDevice& pdevice)
		: device(device)
		, pdevice(pdevice)
	{
		vkGetPhysicalDeviceProperties(pdevice, &pdevProperties);

		stagingBuffer = CreateBuffer(BufferType::TransferSrc, StagingSize);
		stagingMemory = AttachMemory<(VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)>(stagingBuffer);
	}

	uint32_t MemoryLoaderVulkan::Alignment() const
	{
		// assumption: all alignments on gpu memory are the same.
		return static_cast<uint32_t>(pdevProperties.limits.minUniformBufferOffsetAlignment);
	}

	void MemoryLoaderVulkan::LoadDataToMemory(const BufferType type, const std::size_t size, std::function<void(void*)>&& WriteAvailable, std::function<void(const Buffer&)>&& onDone) const
	{
 		assert(size < StagingSize);

		void* data;
		vkMapMemory(device, stagingMemory, 0, VK_WHOLE_SIZE, 0, &data);
		WriteAvailable(data);
		vkUnmapMemory(device, stagingMemory);

		auto buffer = CreateBuffer(static_cast<BufferType>(type | TransferDst), size);
		VkDeviceMemory deviceMemory = AttachMemory<VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT>(buffer);

	}

	VkBuffer MemoryLoaderVulkan::CreateBuffer(const BufferType type, const std::size_t size) const
	{
		VkBuffer buffer;
		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.flags = 0;
		bufferInfo.usage = static_cast<VkBufferUsageFlags>(type);
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		bufferInfo.queueFamilyIndexCount = 0;
		bufferInfo.pQueueFamilyIndices = 0;

		if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to create buffer!");
		}

		return buffer;
	}
}