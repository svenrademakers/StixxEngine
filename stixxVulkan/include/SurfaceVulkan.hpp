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
		uint32_t ImageCount();
		VkPresentModeKHR PresentMode();

	private:
		vk::PhysicalDevice pdevice;
		VkInstance instance;

	public:
		vk::Format surfaceDepthFormat;
		vk::Format surfaceColorFormat;
		vk::ColorSpaceKHR surfaceColorSpace;

		VkExtent2D extent;
		VkSurfaceTransformFlagBitsKHR surfaceTransformFlagBitsKHR;
	};
}

#endif /* RENDERERVULKAN_HPP */
