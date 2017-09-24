#ifndef SURFACE_VULKAN_HPP
#define SURFACE_VULKAN_HPP

#include <string>
#include <vulkan/vulkan.hpp>
#include "InstanceVulkan.hpp"
#include "Window.hpp"
#include "HandleExposer.hpp"

namespace sx
{
	class SurfaceVulkan
		: public HandleExposer<VkSurfaceKHR>
	{
	public:
		SurfaceVulkan() = default;
		virtual ~SurfaceVulkan();

        void Init(vk::Instance& instance,vk::PhysicalDevice& pdevice, Window &window);

		uint32_t ImageCount();
		VkPresentModeKHR PresentMode();
		VkSurfaceFormatKHR Format();
		VkExtent2D Extent();
		VkSurfaceTransformFlagBitsKHR CurrentTransform();
	private:
		vk::PhysicalDevice pdevice;
		VkInstance instance;
		VkSurfaceFormatKHR format;

		vk::Format surfaceDepthFormat;

		VkExtent2D extent;
		VkSurfaceTransformFlagBitsKHR currentTransform;
	};
}

#endif /* RENDERERVULKAN_HPP */
