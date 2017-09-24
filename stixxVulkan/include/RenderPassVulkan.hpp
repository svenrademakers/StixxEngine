#ifndef RENDERPASS_VULKAN_HPP
#define RENDERPASS_VULKAN_HPP

#include "DeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "SwapchainVulkan.hpp"
#include "HandleExposer.hpp"

namespace sx
{
	class RenderPassVulkan
		: public HandleExposer<VkRenderPass>
	{
	public:
		RenderPassVulkan() = default;
		virtual ~RenderPassVulkan();

		void Init(vk::Device& device, SwapchainVulkan& swapchain);
		const std::vector<VkFramebuffer>& FrameBuffers();

	private:
		VkDevice device;
		std::vector<VkFramebuffer> frameBuffers;
	};

}
#endif
