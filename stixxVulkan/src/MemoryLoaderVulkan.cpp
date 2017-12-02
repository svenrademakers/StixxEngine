#include "MemoryLoaderVulkan.hpp"
#include "RendererVulkan.hpp"

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
	MemoryLoaderVulkan::MemoryLoaderVulkan(const VkDevice& device, const VkPhysicalDevice& pdevice, const VkCommandPool& pool, const VkQueue& queue)
		: device(device)
		, pdevice(pdevice)
		, pool(pool)
		, queue(queue)
	{
		vkGetPhysicalDeviceProperties(pdevice, &pdevProperties);

		stagingBuffer = CreateBuffer(BufferType::TransferSrc, StagingSize);
		stagingMemory = AttachMemory<(VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)>(stagingBuffer);

		VkFenceCreateInfo createFence = {};
		createFence.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		createFence.flags = 0;

		vkCreateFence(device, &createFence, nullptr, &transferFence);
	}

	MemoryLoaderVulkan::~MemoryLoaderVulkan()
	{
		vkDestroyBuffer(device, stagingBuffer, nullptr);
		vkDestroyFence(device, transferFence, nullptr);
		vkFreeMemory(device, stagingMemory, nullptr);
	}

	uint32_t MemoryLoaderVulkan::Alignment() const
	{
		// assumption: all alignments on gpu memory are the same.
		return static_cast<uint32_t>(pdevProperties.limits.minUniformBufferOffsetAlignment);
	}

	Buffer MemoryLoaderVulkan::LoadDataToMemory(const BufferType type, const std::size_t size, std::function<void(void*)>&& WriteAvailable) const
	{
 		assert(size < StagingSize);

		void* data;
		vkMapMemory(device, stagingMemory, 0, VK_WHOLE_SIZE, 0, &data);
		WriteAvailable(data);
		vkUnmapMemory(device, stagingMemory);

		auto buffer = CreateBuffer(static_cast<BufferType>(type | TransferDst), size);
		VkDeviceMemory deviceMemory = AttachMemory<VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT>(buffer);

		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = pool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);
		VkBufferCopy copyRegion = {};
		copyRegion.size = size;
		vkCmdCopyBuffer(commandBuffer, stagingBuffer, buffer, 1, &copyRegion);
		vkEndCommandBuffer(commandBuffer);
		
		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(queue, 1, &submitInfo, transferFence);
		vkWaitForFences(device, 1, &transferFence, true, -1);
		vkFreeCommandBuffers(device, pool, 1, &commandBuffer);
		return buffer;
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