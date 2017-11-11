#ifndef MODEL_VULKAN_HPP
#define MODEL_VULKAN_HPP

#include <stdexcept>
#include "vulkan/vulkan.h"
#include "glm/glm.hpp"
#include "util/Observer.hpp"
#include "renderer/Model.hpp"
#include "PipelineVulkan.hpp"

namespace sx
{
	struct Mesh;

	class ModelVulkan
		: public PipelineObserver
		, public Model
	{
	public:
		ModelVulkan(const VkDevice& device, const VkPhysicalDevice& pdevice, PipelineVulkan& pipeline, const sx::Mesh& mesh);
		virtual ~ModelVulkan();

		void LoadDescriptors(const VkDescriptorSetLayout& descriptorSetLayout);
		void Draw(const VkPipelineLayout& pipelineLayout, const VkCommandBuffer& drawCmdBuffer);

		// PipelineObserver
		void PipelineLayoutCreated(VkPipelineLayoutCreateInfo& info) override;

		// Model
		void UpdateUbo(UniformBufferObject& ubo) override;

	private:
		template<VkBufferUsageFlags flags>
		void LoadBuffer(VkBuffer& buffer, const std::size_t size) const
		{
			VkBufferCreateInfo bufferInfo = {};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = size;
			bufferInfo.flags = 0;
			bufferInfo.usage = flags;
			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			bufferInfo.queueFamilyIndexCount = 0;
			bufferInfo.pQueueFamilyIndices = 0;
			vkCreateBuffer(device, &bufferInfo, nullptr, &buffer);

			if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
				throw std::runtime_error("failed to create buffer!");
			}
		}

		VkDeviceMemory AttachMemory(VkBuffer& buffer) const;
		void LoadVertexData(const Mesh& mesh);
		void SetupUboBuffer();
		void CreateDescriptorPool();

	private:
		const VkDevice& device;
		const VkPhysicalDevice& pdevice;

		const std::size_t vertexSize;
		const std::uint32_t indicesCount;
		const std::size_t indexSize;

		VkBuffer buffer;
		VkDeviceMemory deviceMemory;
		VkMappedMemoryRange memRange;

		UniformBufferObject ubo;
		VkBuffer uboBuffer;
		VkDeviceMemory uboMemory;
		VkMappedMemoryRange uboMemRange;

		VkDescriptorPool descriptorPool;
		VkDescriptorSet descriptorSet;
	};
}
#endif