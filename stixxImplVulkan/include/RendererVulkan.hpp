#ifndef RENDERERVULKAN_HPP
#define RENDERERVULKAN_HPP

#include <string>
#include "Window.hpp"
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
		void Draw() override;

	private:
		Window& window;
	};
}

#endif /* RENDERERVULKAN_HPP */
