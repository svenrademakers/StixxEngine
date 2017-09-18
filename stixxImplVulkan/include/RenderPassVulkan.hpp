#ifndef RENDERPASS_VULKAN_HPP
#define RENDERPASS_VULKAN_HPP

#include <vulkan\vulkan.hpp>
#include "DeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "SwapChainVulkan.hpp"
#include "HandleExposer.hpp"

namespace sx
{
	class RenderPassVulkan
		: public HandleExposer<VkRenderPass>
	{
	public:
		RenderPassVulkan(DeviceVulkan& device, SwapchainVulkan& swapchain);
		virtual ~RenderPassVulkan();

		const std::vector<VkFramebuffer>& FrameBuffers();

	private:
		DeviceVulkan& device;
		std::vector<VkFramebuffer> frameBuffers;
	};

}
#endif