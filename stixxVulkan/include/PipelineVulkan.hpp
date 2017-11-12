#ifndef PIPELINE_VULKAN_HPP
#define PIPELINE_VULKAN_HPP

#include "DeviceVulkan.hpp"
#include "ShaderVulkan.hpp"
#include "RenderPassVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "utils/CastOperator.hpp"
#include "utils/Observer.hpp"

namespace sx
{
	class PipelineObserver
		: public Observer<PipelineObserver>
	{
	public:
		using Observer<PipelineObserver>::Observer;
		virtual void PipelineLayoutCreated(VkPipelineLayoutCreateInfo& info) = 0;
	};

	class PipelineVulkan
		: public CastOperator<VkPipeline>
		, public Subject<PipelineObserver>
	{
	public:
		PipelineVulkan(const VkDevice& device);
		virtual ~PipelineVulkan();

		void Init(RenderPassVulkan& renderpass, SurfaceVulkan& surface, ShaderVertexVulkan& vertex, ShaderFragmentVulkan& fragment, VkViewport& viewport);
		const VkPipelineLayout& Layout();
		const VkDescriptorSetLayout& DescriptorSet();

	private:
		const VkDevice& device;
		VkPipelineLayout pipelineLayout;
		VkDescriptorSetLayout descriptorSetLayout;
	};
}
#endif
