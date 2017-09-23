#ifndef SWAPCHAIN_VULKAN_HPP
#define SWAPCHAIN_VULKAN_HPP

#include <vector>
#include "vulkan/vulkan.h"
#include "DeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "HandleExposer.hpp"

namespace sx
{
	class SwapchainVulkan
		: public HandleExposer<VkSwapchainKHR>
	{
	public:
		SwapchainVulkan() = default;
		virtual ~SwapchainVulkan();

		void Init(vk::Device& device, SurfaceVulkan&  surface);

	public:
		std::vector<VkImageView>& ImageViews();

		// mmhh
		VkFormat Format();
		VkExtent2D Extent();

	private:
		std::vector<VkImageView> swapChainImageViews;
		VkFormat format;
		VkExtent2D extent;
		VkDevice device;
	};
}

#endif /* SWAPCHAIN_VULKAN_HPP */

