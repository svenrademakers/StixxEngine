#ifndef RENDERPASS_VULKAN_HPP
#define RENDERPASS_VULKAN_HPP

#include "DeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "SwapchainVulkan.hpp"
#include "CastOperator.hpp"

namespace sx
{
	class RenderPassVulkan
		: public CastOperator<VkRenderPass>
	{
	public:
		RenderPassVulkan() = default;
		virtual ~RenderPassVulkan();

		void Init(const VkDevice& device, SwapchainVulkan& swapchain, SurfaceVulkan& surface);
		const std::vector<VkFramebuffer>& FrameBuffers();

	private:
		VkDevice device;
		std::vector<VkFramebuffer> frameBuffers;
	};

}
#endif
