#include "ModelVulkan.hpp"


namespace sx
{
	ModelVulkan::ModelVulkan(sx::DeviceVulkan& device, sx::PhysicalDeviceVulkan& pdevice, const sx::Mesh& mesh)
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
	
	VkDeviceMemory ModelVulkan::AttachMemory(VkBuffer& buffer)
	{
		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = pdevice.FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if (vkAllocateMemory(device, &allocInfo, nullptr, &deviceMemory) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate buffer memory!");
		}
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