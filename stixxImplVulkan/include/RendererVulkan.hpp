#ifndef RENDERER_VULKAN_HPP
#define RENDERER_VULKAN_HPP

#include "Renderer.hpp"
#include "PipelineVulkan.hpp"
#include "DeviceVulkan.hpp"
#include "vulkan\vulkan.hpp"

namespace sx
{
	class RendererVulkan
		: public Renderer
	{
	public:
		RendererVulkan(DeviceVulkan& device, PipelineVulkan& pipeline, RenderPassVulkan& renderpass, SwapchainVulkan& swapchain, vk::PhysicalDevice& physicalDevice);
		RendererVulkan(const RendererVulkan&) = delete;
		RendererVulkan& operator = (const RendererVulkan&) = delete;
		virtual ~RendererVulkan();

		void Draw() override;

	private:
		vk::Device device;
		PipelineVulkan& pipeline;
		SwapchainVulkan& swapchain;
		uint32_t graphicsFamilyIndex;
	};
}

#endif /* RENDERERVULKAN_HPP */
