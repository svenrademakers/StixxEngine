#ifndef PIPELINE_VULKAN_HPP
#define PIPELINE_VULKAN_HPP

#include "DeviceVulkan.hpp"
#include "ShaderVulkan.hpp"
#include "RenderPassVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "CastOperator.hpp"

namespace sx
{
	class PipelineVulkan
		: public CastOperator<VkPipeline>
	{
	public:
		PipelineVulkan() = default;
		virtual ~PipelineVulkan();

		void Init(const VkDevice& device, RenderPassVulkan& renderpass, SurfaceVulkan& surface, ShaderVertexVulkan& vertex, ShaderFragmentVulkan& fragment, VkViewport& viewport);

	private:
		VkDevice device;
		VkPipelineLayout pipelineLayout;
	};
}
#endif
