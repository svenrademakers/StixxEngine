#ifndef MODEL_VULKAN_HPP
#define MODEL_VULKAN_HPP

#include "DeviceVulkan.hpp"
#include "PhysicalDeviceVulkan.hpp"
#include "Mesh.hpp"

namespace sx
{
	class ModelVulkan
	{
	public:
		 ModelVulkan(sx::DeviceVulkan& device, sx::PhysicalDeviceVulkan& pdevice, const sx::Mesh& mesh);
		virtual ~ModelVulkan();

		void Draw(const VkCommandBuffer& drawCmdBuffer);

	private:
		template<VkBufferUsageFlags flags, class T>
		void LoadBuffer(const std::vector<T>& bufferData, VkBuffer& buffer, VkDeviceMemory& deviceMemory)
		{
			const std::size_t bufferSize = sizeof(T) * bufferData.size();

			VkBufferCreateInfo bufferInfo = {};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = bufferSize;
			bufferInfo.flags = 0;
			bufferInfo.usage = flags;
			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			bufferInfo.queueFamilyIndexCount = 0;
			bufferInfo.pQueueFamilyIndices = 0;
			vkCreateBuffer(device, &bufferInfo, nullptr, &buffer);

			if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
				throw std::runtime_error("failed to create buffer!");
			}

			VkMemoryRequirements memRequirements;
			vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

			VkMemoryAllocateInfo allocInfo = {};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = pdevice.FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			if (vkAllocateMemory(device, &allocInfo, nullptr, &deviceMemory) != VK_SUCCESS) {
				throw std::runtime_error("failed to allocate buffer memory!");
			}

			vkBindBufferMemory(device, buffer, deviceMemory, 0);
			void* data;
			vkMapMemory(device, deviceMemory, 0, bufferSize, 0, &data);
			memcpy(data, bufferData.data(), (size_t)bufferSize);
			vkUnmapMemory(device, deviceMemory);
		}

	private:
		sx::DeviceVulkan& device;
		sx::PhysicalDeviceVulkan& pdevice;

		VkBuffer indexBuffer;
		VkBuffer vertexBuffer;
		const uint32_t indicesCount;
		VkDeviceMemory vertexMem;
		VkDeviceMemory indexMem;
	};
}
#endif