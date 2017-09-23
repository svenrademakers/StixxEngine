#ifndef PIPELINE_VULKAN_HPP
#define PIPELINE_VULKAN_HPP

#include "DeviceVulkan.hpp"
#include "ShaderVulkan.hpp"
#include "RenderPassVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "HandleExposer.hpp"

namespace sx
{
	class PipelineVulkan
		: public HandleExposer<VkPipeline>
	{
	public:
		PipelineVulkan() = default;
		virtual ~PipelineVulkan();

		void Init(vk::Device& device, RenderPassVulkan& renderpass, SurfaceVulkan& surface, ShaderVertexVulkan& vertex, ShaderFragmentVulkan& fragment, vk::Viewport& viewport);

	private:
		VkDevice device;
		VkPipelineLayout pipelineLayout;
	};
}
#endif
