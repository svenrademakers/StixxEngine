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
		template<VkBufferUsageFlags flags>
		void LoadBuffer(const Mesh& mesh, VkBuffer& buffer, VkDeviceMemory& deviceMemory)
		{
			VkBufferCreateInfo bufferInfo = {};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = vertexSize + indexSize;
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

			void* data = nullptr;
			vkBindBufferMemory(device, buffer, deviceMemory, 0);

			vkMapMemory(device, deviceMemory, 0, vertexSize, 0, &data);
			memcpy(data, mesh.vertices.data(), vertexSize);
			vkUnmapMemory(device, deviceMemory);

			vkMapMemory(device, deviceMemory, vertexSize, indexSize, 0, &data);
			memcpy(data, mesh.indices.data(), indexSize);
			vkUnmapMemory(device, deviceMemory);
		}

	private:
		sx::DeviceVulkan& device;
		sx::PhysicalDeviceVulkan& pdevice;

		const std::size_t vertexSize;
		const std::uint32_t indicesCount;
		const std::size_t indexSize;

		VkBuffer buffer;
		VkDeviceMemory deviceMemory;
	};
}
#endif