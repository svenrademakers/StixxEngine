#ifndef RENDERER_VULKAN_HPP
#define RENDERER_VULKAN_HPP

#include "Renderer.hpp"
#include "PipelineVulkan.hpp"
#include "DeviceVulkan.hpp"
namespace sx
{
	class RendererVulkan
		: public Renderer
	{
	public:
		RendererVulkan(DeviceVulkan& device, PipelineVulkan& pipeline, RenderPassVulkan& renderpass, SwapchainVulkan& swapchain);
		RendererVulkan(const RendererVulkan&) = delete;
		RendererVulkan& operator = (const RendererVulkan&) = delete;
		virtual ~RendererVulkan();

		void Draw() override;

	private:
		DeviceVulkan& device;
		PipelineVulkan& pipeline;
		SwapchainVulkan& swapchain;
	};
}

#endif /* RENDERERVULKAN_HPP */
