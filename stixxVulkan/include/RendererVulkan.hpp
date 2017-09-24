#ifndef RENDERER_VULKAN_HPP
#define RENDERER_VULKAN_HPP

#include "Renderer.hpp"
#include "vulkan/vulkan.hpp"
#include <WindowGlfw.hpp>
#include "SwapchainVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "RenderPassVulkan.hpp"
#include "PipelineVulkan.hpp"

namespace sx
{
    class  ShaderVertexVulkan;
    class ShaderFragmentVulkan;

	class RendererVulkan
		: public Renderer
	{
	public:
        RendererVulkan(sx::Window& window, const std::vector<uint32_t>& vertex, const std::vector<uint32_t>& fragment);
        RendererVulkan(const RendererVulkan&) = delete;
		RendererVulkan& operator = (const RendererVulkan&) = delete;
		virtual ~RendererVulkan();

        void LoadScene(const std::vector<sx::Vertex>& vertex, const std::vector<uint32_t>& indices) override;
		void LoadDrawingCommands();
		void Draw() override;

	private:
		vk::Instance instance;
		vk::PhysicalDevice pdevice;
		vk::Device device;
		vk::CommandPool commandPool;
		std::vector<vk::CommandBuffer> commandBuffers;
		VkQueue graphicsQueue;
		vk::Buffer buffer;
        SurfaceVulkan surface;
        SwapchainVulkan swapchain;
        RenderPassVulkan renderPass;
        PipelineVulkan pipeline;
	};
}

#endif /* RENDERERVULKAN_HPP */
