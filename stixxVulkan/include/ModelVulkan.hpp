#ifndef MODEL_VULKAN_HPP
#define MODEL_VULKAN_HPP

#include <stdexcept>
#include "vulkan/vulkan.h"
#include "glm/glm.hpp"
#include "infra/Observer.hpp"
#include "interfaces/renderer/Model.hpp"
#include "PipelineVulkan.hpp"
#include "RendererVulkan.hpp" 

namespace sx
{
	struct Mesh;

	class ModelVulkan
		: public PipelineObserver
		, public Model
	{
	public:
		ModelVulkan(const VkDevice& device, const VkPhysicalDevice& pdevice, PipelineVulkan& pipeline, const sx::Mesh& mesh, GPUMemoryLoader& loader);
		virtual ~ModelVulkan();

		void LoadDescriptors(const VkDescriptorSetLayout& descriptorSetLayout);
		void Draw(const VkPipelineLayout& pipelineLayout, const VkCommandBuffer& drawCmdBuffer);

		// PipelineObserver
		void PipelineLayoutCreated(VkPipelineLayoutCreateInfo& info) override;

		// Model
		void UpdateUbo(UniformBufferObject& ubo) override;

	private:
	
		void LoadVertexData(const Mesh& mesh);
		void SetupUboBuffer();
		void CreateDescriptorPool();

	private:
		const VkDevice& device;
		const VkPhysicalDevice& pdevice;

		const std::size_t vertexSize;
		const std::uint32_t indicesCount;
		const std::size_t indexSize;

		GPUMemoryLoader& memoryLoader;

		Buffer buffer;

		VkBuffer uboBuffer;
		VkDeviceMemory uboMemory;
		VkMappedMemoryRange uboMemRange;

		VkDescriptorPool descriptorPool;
		VkDescriptorSet descriptorSet;
	};
}
#endif