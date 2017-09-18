#ifndef SWAPCHAIN_VULKAN_HPP
#define SWAPCHAIN_VULKAN_HPP

#include <vector>
#include <vulkan\vulkan.h>
#include "DeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "HandleExposer.hpp"

namespace sx
{
	class SwapchainVulkan
		: public HandleExposer<VkSwapchainKHR>
	{
	public:
		SwapchainVulkan(DeviceVulkan& device, SurfaceVulkan&  surface);
		virtual ~SwapchainVulkan();

	public:
		std::vector<VkImageView>& ImageViews();

		// mmhh
		VkFormat Format();
		VkExtent2D Extent();

	private:
		DeviceVulkan& device;
		std::vector<VkImageView> swapChainImageViews;
		VkFormat format;
		VkExtent2D extent;
	};
}

#endif /* SWAPCHAIN_VULKAN_HPP */
