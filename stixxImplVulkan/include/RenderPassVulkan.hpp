#ifndef RENDERPASS_VULKAN_HPP
#define RENDERPASS_VULKAN_HPP

#include <vector>
#include <vulkan\vulkan.hpp>

namespace sx
{
	class RenderPassVulkan
	{
	public:
		RenderPassVulkan(const VkDevice& device, const VkFormat& format);
		RenderPassVulkan(const RenderPassVulkan&) = delete;
		RenderPassVulkan& operator= (const RenderPassVulkan&) = delete;
		virtual ~RenderPassVulkan();

		const VkRenderPass& RenderPass();

	private:
		const VkDevice& device;
		VkRenderPass renderPass;
	};

}
#endif