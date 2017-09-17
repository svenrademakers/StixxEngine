#ifndef SWAPCHAIN_VULKAN_HPP
#define SWAPCHAIN_VULKAN_HPP

#include <vector>
#include <vulkan\vulkan.h>
#include "DeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"

namespace sx
{
	class SwapchainVulkan
	{
	public:
		SwapchainVulkan(DeviceVulkan& device, SurfaceVulkan&  surface);
		SwapchainVulkan(const SwapchainVulkan&) = delete;
		SwapchainVulkan& operator = (const SwapchainVulkan&) = delete;
		virtual ~SwapchainVulkan() = default;

	public:
		std::vector<VkImageView>& ImageViews();

		// mmhh
		VkFormat Format();
		VkExtent2D Extent();
		const VkSwapchainKHR& Swapchain();

	private:
		DeviceVulkan& device;
		VkSwapchainKHR swapChain;
		std::vector<VkImageView> swapChainImageViews;
		VkFormat format;
		VkExtent2D extent;
	};
}

#endif /* RENDERERVULKAN_HPP */
