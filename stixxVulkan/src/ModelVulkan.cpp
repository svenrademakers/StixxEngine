#include "ModelVulkan.hpp"

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
	ModelVulkan::ModelVulkan(const VkDevice& device, const VkPhysicalDevice& pdevice, const sx::Mesh& mesh)
		: device(device)
		, pdevice(pdevice)
		, vertexSize(sizeof(mesh.vertices[0]) * mesh.vertices.size())
		, indicesCount(mesh.indices.size())
		, indexSize(4 * static_cast<std::size_t>(indicesCount))
	{
		LoadVertexData(mesh);
		
		LoadBuffer<VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT>(uboBuffer, sizeof(UniformBufferObject));
		uboMemory = AttachMemory(uboBuffer);
	}

	ModelVulkan::~ModelVulkan()
	{
		vkDestroyBuffer(device, buffer, nullptr);
		vkFreeMemory(device, deviceMemory, nullptr);
	}

	void ModelVulkan::Draw(const VkCommandBuffer& drawCmdBuffer)
	{
		VkDeviceSize offset = 0;
		vkCmdBindVertexBuffers(drawCmdBuffer, 0, 1, &buffer, &offset);
		vkCmdBindIndexBuffer(drawCmdBuffer, buffer, vertexSize, VK_INDEX_TYPE_UINT32);
		vkCmdDrawIndexed(drawCmdBuffer, indicesCount, 1, 0, 0, 0);
	}
	
	VkDeviceMemory ModelVulkan::AttachMemory(VkBuffer& buffer) const 
	{
		VkDeviceMemory deviceMemory;
		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(pdevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if (vkAllocateMemory(device, &allocInfo, nullptr, &deviceMemory) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate buffer memory!");
		}

		return deviceMemory;
	}

	void ModelVulkan::LoadVertexData(const Mesh& mesh)
	{
		LoadBuffer<VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT>(buffer, vertexSize + indexSize);
		deviceMemory = AttachMemory(buffer);

		void* data = nullptr;
		vkBindBufferMemory(device, buffer, deviceMemory, 0);

		vkMapMemory(device, deviceMemory, 0, vertexSize, 0, &data);
		memcpy(data, mesh.vertices.data(), vertexSize);
		vkUnmapMemory(device, deviceMemory);

		vkMapMemory(device, deviceMemory, vertexSize, indexSize, 0, &data);
		memcpy(data, mesh.indices.data(), indexSize);
		vkUnmapMemory(device, deviceMemory);
	}
}