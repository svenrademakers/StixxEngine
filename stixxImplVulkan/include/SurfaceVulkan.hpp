#ifndef SURFACE_VULKAN_HPP
#define SURFACE_VULKAN_HPP

#include <string>
#include <vulkan/vulkan.hpp>
#include "InstanceVulkan.hpp"
#include "WindowGlfw.hpp"
#include "HandleExposer.hpp"

namespace sx
{
	class SurfaceVulkan
		: public HandleExposer<VkSurfaceKHR>
	{
	public:
		SurfaceVulkan() = default;
		virtual ~SurfaceVulkan();

        void Init(vk::Instance& instance,vk::PhysicalDevice& pdevice, GLFWwindow &window);

		const VkFormat Format();
		uint32_t ImageCount();
		VkExtent2D& Extent();
		VkColorSpaceKHR ColorSpace();
		VkSurfaceTransformFlagBitsKHR CurrentTransform();

	private:
		uint32_t imageCount;
		VkExtent2D extent;
		VkSurfaceTransformFlagBitsKHR surfaceTransformFlagBitsKHR;
        VkInstance instance;
	};
}

#endif /* RENDERERVULKAN_HPP */
