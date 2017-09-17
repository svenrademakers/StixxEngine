#ifndef RENDERPASS_VULKAN_HPP
#define RENDERPASS_VULKAN_HPP

#include <vulkan\vulkan.hpp>
#include "DeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "SwapChainVulkan.hpp"

namespace sx
{
	class RenderPassVulkan
	{
	public:
		RenderPassVulkan(DeviceVulkan& device, SwapchainVulkan& swapchain);
		RenderPassVulkan(const RenderPassVulkan&) = delete;
		RenderPassVulkan& operator= (const RenderPassVulkan&) = delete;
		virtual ~RenderPassVulkan();

		const VkRenderPass& RenderPass();
		const std::vector<VkFramebuffer>& FrameBuffers();

	private:
		DeviceVulkan& device;
		VkRenderPass renderPass;
		std::vector<VkFramebuffer> frameBuffers;
	};

}
#endif