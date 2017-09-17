#ifndef SURFACE_VULKAN_HPP
#define SURFACE_VULKAN_HPP

#include <string>
#include "InstanceVulkan.hpp"
#include "WindowGlfw.hpp"

namespace sx
{
	class SurfaceVulkan
	{
	public:
		SurfaceVulkan::SurfaceVulkan(InstanceVulkan& instance, GLFWwindow& window);
		SurfaceVulkan(const SurfaceVulkan&) = delete;
		SurfaceVulkan& operator = (const SurfaceVulkan&) = delete;
		virtual ~SurfaceVulkan() = default;

		const VkSurfaceKHR& Surface();
		const VkSurfaceFormatKHR Format();

	private:
		VkSurfaceKHR surface;		
	};
}

#endif /* RENDERERVULKAN_HPP */
