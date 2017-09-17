#ifndef PIPELINE_VULKAN_HPP
#define PIPELINE_VULKAN_HPP

#include <vulkan\vulkan.hpp>
#include "DeviceVulkan.hpp"
#include "ShaderVulkan.hpp"
#include "RenderPassVulkan.hpp"
#include "SurfaceVulkan.hpp"
namespace sx
{
	class PipelineVulkan
	{
	public:
		PipelineVulkan(DeviceVulkan& device, RenderPassVulkan& renderpass, SurfaceVulkan& surface, const std::vector<uint32_t>& vertex, const std::vector<uint32_t>& fragment);
		PipelineVulkan(const PipelineVulkan&) = delete;
		PipelineVulkan& operator=(const PipelineVulkan&) = delete;
		virtual ~PipelineVulkan();

		const VkPipeline& Pipeline();

	private:
		DeviceVulkan& device;
		VkPipeline graphicsPipeline;
		VkPipelineLayout pipelineLayout;
	};
}
#endif