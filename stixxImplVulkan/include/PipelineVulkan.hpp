#ifndef PIPELINE_VULKAN_HPP
#define PIPELINE_VULKAN_HPP

#include <vulkan\vulkan.hpp>
#include "ShaderVulkan.hpp"
#include "RenderPassVulkan.hpp"

namespace sx
{
	class PipelineVulkan
	{
	public:
		PipelineVulkan(const VkDevice& device, RenderPassVulkan& renderpass, const VkExtent2D& extent, ShaderVertexVulkan& vertex, ShaderFragmentVulkan& fragment);
		PipelineVulkan(const PipelineVulkan&) = delete;
		PipelineVulkan& operator=(const PipelineVulkan&) = delete;
		virtual ~PipelineVulkan();

		const VkPipeline& Pipeline();

	private:
		const VkDevice& device;
		VkPipeline graphicsPipeline;
		VkPipelineLayout pipelineLayout;
	};
}
#endif