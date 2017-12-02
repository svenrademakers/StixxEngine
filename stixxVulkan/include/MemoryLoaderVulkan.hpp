#ifndef MEMORY_LOADER_VULKAN_HPP
#define MEMORY_LOADER_VULKAN_HPP

#include "interfaces/renderer/Renderer.hpp"
#include "vulkan/vulkan.h"

namespace sx
{
	class MemoryLoaderVulkan
		: public GPUMemoryLoader
	{
	public:
		const int StagingSize = 1024*256;
		MemoryLoaderVulkan(const VkDevice& device, const VkPhysicalDevice& pdevice, const VkCommandPool& pool, const VkQueue& queue);
		virtual ~MemoryLoaderVulkan();

		//GPUMemoryLoader
		uint32_t Alignment() const override;
		Buffer LoadDataToMemory(const BufferType type, const std::size_t size, std::function<void(void*)>&& WriteAvailable) const override;

	private:
		VkBuffer CreateBuffer(const BufferType type, const std::size_t size) const;

		template<uint32_t MemoryProperty>
		VkDeviceMemory AttachMemory(const VkBuffer& buffer) const
		{
			VkDeviceMemory deviceMemory;
			VkMemoryRequirements memRequirements;
			vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = FindMemoryType(pdevice, memRequirements.memoryTypeBits, static_cast<VkMemoryPropertyFlagBits>(MemoryProperty));

			if (vkAllocateMemory(device, &allocInfo, nullptr, &deviceMemory) != VK_SUCCESS) {
				throw std::runtime_error("failed to allocate buffer memory!");
			}

			vkBindBufferMemory(device, buffer, deviceMemory, 0);

			return deviceMemory;
		}

		const VkDevice& device;
		const VkPhysicalDevice& pdevice;
		const VkCommandPool& pool;
		const VkQueue& queue;

		VkPhysicalDeviceProperties pdevProperties;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingMemory;
		VkFence transferFence;
	};
}

#endif