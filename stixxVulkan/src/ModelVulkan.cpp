#include "ModelVulkan.hpp"

namespace sx
{
	ModelVulkan::ModelVulkan(sx::DeviceVulkan& device, sx::PhysicalDeviceVulkan& pdevice, const sx::Mesh& mesh)
		: device(device)
		, pdevice(pdevice)
		, indicesCount(static_cast<uint32_t>(sizeof(mesh.indices[0])* mesh.indices.size()))
	{
		LoadBuffer<VK_BUFFER_USAGE_VERTEX_BUFFER_BIT>
			(mesh.vertices, vertexBuffer, vertexMem);
		LoadBuffer<VK_BUFFER_USAGE_INDEX_BUFFER_BIT>
			(mesh.indices, indexBuffer, indexMem);
	}

	ModelVulkan::~ModelVulkan()
	{
		vkDestroyBuffer(device, indexBuffer, nullptr);
		vkDestroyBuffer(device, indexBuffer, nullptr);

		vkFreeMemory(device, vertexMem, nullptr);
		vkFreeMemory(device, indexMem, nullptr);
	}

	void ModelVulkan::Draw(const VkCommandBuffer& drawCmdBuffer)
	{
		VkDeviceSize offset = 0;
		vkCmdBindVertexBuffers(drawCmdBuffer, 0, 1, &vertexBuffer, &offset);
		vkCmdBindIndexBuffer(drawCmdBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
		vkCmdDrawIndexed(drawCmdBuffer, indicesCount, 1, 0, 0, 0);
	}
}