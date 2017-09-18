#ifndef SURFACE_VULKAN_HPP
#define SURFACE_VULKAN_HPP

#include <string>
#include "InstanceVulkan.hpp"
#include "WindowGlfw.hpp"
#include "HandleExposer.hpp"

namespace sx
{
	class SurfaceVulkan 
		: public HandleExposer<VkSurfaceKHR>
	{
	public:
		SurfaceVulkan(InstanceVulkan& instance, GLFWwindow& window);
		virtual ~SurfaceVulkan();

		const VkFormat Format();
		uint32_t ImageCount();
		VkExtent2D& Extent();
		VkColorSpaceKHR ColorSpace();
		VkSurfaceTransformFlagBitsKHR CurrentTransform();

	private:
		InstanceVulkan& instance;

		uint32_t imageCount;
		VkExtent2D extent;
		VkSurfaceTransformFlagBitsKHR surfaceTransformFlagBitsKHR;
	};
}

#endif /* RENDERERVULKAN_HPP */
