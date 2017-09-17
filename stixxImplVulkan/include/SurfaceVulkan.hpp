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
		SurfaceVulkan(InstanceVulkan& instance, GLFWwindow& window);
		SurfaceVulkan(const SurfaceVulkan&) = delete;
		SurfaceVulkan& operator = (const SurfaceVulkan&) = delete;
		virtual ~SurfaceVulkan() = default;

		const VkSurfaceKHR& Surface();
		const VkFormat Format();
		uint32_t ImageCount();
		VkExtent2D& Extent();
		VkColorSpaceKHR ColorSpace();
		VkSurfaceTransformFlagBitsKHR CurrentTransform();

	private:
		VkSurfaceKHR surface;
		uint32_t imageCount;
		VkExtent2D extent;
		VkSurfaceTransformFlagBitsKHR surfaceTransformFlagBitsKHR;
	};
}

#endif /* RENDERERVULKAN_HPP */
