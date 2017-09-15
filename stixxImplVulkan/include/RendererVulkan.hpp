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
		RendererVulkan(Window& window, const std::vector<uint32_t>& vertex, const std::vector<uint32_t>& fragment);
		RendererVulkan(const RendererVulkan&) = delete;
		RendererVulkan& operator = (const RendererVulkan&) = delete;
		virtual ~RendererVulkan();

		void CreateSurface(WindowGlfw& window) const override;
		void Draw() override;

	private:
		Window& window;
	};
}

#endif /* RENDERERVULKAN_HPP */
