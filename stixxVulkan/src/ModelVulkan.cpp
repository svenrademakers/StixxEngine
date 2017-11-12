#include "ModelVulkan.hpp"
#include "renderer/Mesh.hpp"
#include <iostream>

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
	ModelVulkan::ModelVulkan(const VkDevice& device, const VkPhysicalDevice& pdevice, PipelineVulkan& pipeline, const sx::Mesh& mesh)
		: PipelineObserver(pipeline)
		, device(device)
		, pdevice(pdevice)
		, vertexSize(sizeof(mesh.vertices[0]) * mesh.vertices.size())
		, indicesCount(mesh.indices.size())
		, indexSize(4 * static_cast<const std::size_t>(indicesCount))
		, descriptorPool(nullptr)
		, descriptorSet(nullptr)
	{
		CreateDescriptorPool();
		LoadVertexData(mesh);
		SetupUboBuffer();
	}

	ModelVulkan::~ModelVulkan()
	{
		vkDestroyBuffer(device, buffer, nullptr);
		vkDestroyBuffer(device, uboBuffer, nullptr);
		vkFreeMemory(device, deviceMemory, nullptr);
		vkFreeMemory(device, uboMemory, nullptr);

		vkDestroyDescriptorPool(device, descriptorPool, nullptr);
	}

	void ModelVulkan::LoadDescriptors(const VkDescriptorSetLayout& descriptorSetLayout)
	{
		VkDescriptorSetAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = descriptorPool;
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &descriptorSetLayout;

		if (vkAllocateDescriptorSets(device, &allocInfo, &descriptorSet) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate descriptor set!");
		}

		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = uboBuffer;
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(UniformBufferObject);

		VkWriteDescriptorSet descriptorWrite = {};
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = descriptorSet;
		descriptorWrite.dstBinding = 0;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pBufferInfo = &bufferInfo;

		vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
	}

	void ModelVulkan::Draw(const VkPipelineLayout& pipelineLayout, const VkCommandBuffer& drawCmdBuffer)
	{
		assert(descriptorSet != nullptr);

		vkCmdBindDescriptorSets(drawCmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);

		VkDeviceSize offset = 0;
		vkCmdBindVertexBuffers(drawCmdBuffer, 0, 1, &buffer, &offset);
		vkCmdBindIndexBuffer(drawCmdBuffer, buffer, vertexSize, VK_INDEX_TYPE_UINT32);

		vkCmdDrawIndexed(drawCmdBuffer, indicesCount, 1, 0, 0, 0);
	}

	void ModelVulkan::PipelineLayoutCreated(VkPipelineLayoutCreateInfo& info)
	{
		LoadDescriptors(*info.pSetLayouts);
	}

	void ModelVulkan::UpdateUbo(UniformBufferObject& ubos)
	{
		// naivly update ubo
		void* data;
		vkMapMemory(device, uboMemory, 0, sizeof(ubos), 0, &data);
		memcpy(data, &ubos, sizeof(ubos));
		vkUnmapMemory(device, uboMemory);
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

	void ModelVulkan::SetupUboBuffer()
	{
		LoadBuffer<VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT>(uboBuffer, sizeof(UniformBufferObject));
		uboMemory = AttachMemory(uboBuffer);
		vkBindBufferMemory(device, uboBuffer, uboMemory, 0);
	}

	void ModelVulkan::CreateDescriptorPool() {
		VkDescriptorPoolSize poolSize = {};
		poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSize.descriptorCount = 1;

		VkDescriptorPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = 1;
		poolInfo.pPoolSizes = &poolSize;
		poolInfo.maxSets = 1;

		if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor pool!");
		}
	}
}