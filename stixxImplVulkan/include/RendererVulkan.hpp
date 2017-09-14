#ifndef RENDERER_VULKAN_HPP
#define RENDERER_VULKAN_HPP

#include <string>

#include "WindowGlfw.hpp"
#include "Renderer.hpp"

namespace sx
{
	class RendererVulkan
		: public Renderer
	{
	public:
		RendererVulkan(Window& window);
		RendererVulkan(const RendererVulkan&) = delete;
		RendererVulkan& operator = (const RendererVulkan&) = delete;
		virtual ~RendererVulkan();

		void CreateSurface(WindowGlfw& window) const override;
		void Draw() override;

	private:
		void CreateLogicDevice() const;
		void CreateSwapChain() const;
		void CreateImageViews() const;
		void CreateRenderPass() const;
		void createGraphicsPipeline() const;
		void CreateFramebuffers() const;
		void CreateCommandPool() const;
		void CreateCommandBuffers() const;
		void CreateSemaphores() const;

	private:
		Window& window;
	};
}

#endif /* RENDERERVULKAN_HPP */
