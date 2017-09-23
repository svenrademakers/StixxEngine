#ifndef RENDERER_VULKAN_HPP
#define RENDERER_VULKAN_HPP

#include "Renderer.hpp"
#include "PipelineVulkan.hpp"
#include "DeviceVulkan.hpp"

namespace vk
{
	class PhysicalDevice;
}

namespace sx
{
	class RendererVulkan
		: public Renderer
	{
	public:
		RendererVulkan(DeviceVulkan& device, PipelineVulkan& pipeline, RenderPassVulkan& renderpass, SwapchainVulkan& swapchain, const VkPhysicalDevice& physicalDevice);
		RendererVulkan(const RendererVulkan&) = delete;
		RendererVulkan& operator = (const RendererVulkan&) = delete;
		virtual ~RendererVulkan();

		void Draw() override;

	private:
		PipelineVulkan& pipeline;
		SwapchainVulkan& swapchain;
		uint32_t graphicsFamilyIndex;
	};
}

#endif /* RENDERERVULKAN_HPP */
