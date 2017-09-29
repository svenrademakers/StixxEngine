#ifndef SWAPCHAIN_VULKAN_HPP
#define SWAPCHAIN_VULKAN_HPP

#include <vector>
#include "vulkan/vulkan.h"
#include "DeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "CastOperator.hpp"


namespace sx
{
	class SwapchainVulkan
		: public CastOperator<VkSwapchainKHR>
	{
	public:
		SwapchainVulkan() = default;
		virtual ~SwapchainVulkan();

		void Init(const VkDevice& device, SurfaceVulkan& surface);
		uint32_t NumberOfImages();

	public:
		std::vector<VkImageView>& ImageViews();

	private:
		std::vector<VkImageView> swapChainImageViews;
		VkDevice device;
	};
}

#endif /* SWAPCHAIN_VULKAN_HPP */

