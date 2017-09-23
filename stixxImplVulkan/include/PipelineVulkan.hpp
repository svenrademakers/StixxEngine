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
		PipelineVulkan(DeviceVulkan& device, RenderPassVulkan& renderpass, SurfaceVulkan& surface, const std::vector<char>& vertex, const std::vector<char>& fragment);
		virtual ~PipelineVulkan();

	private:
		DeviceVulkan& device;
		VkPipelineLayout pipelineLayout;
	};
}
#endif
