#ifndef SWAPCHAIN_VULKAN_HPP
#define SWAPCHAIN_VULKAN_HPP

#include <vector>
#include "vulkan/vulkan.h"
#include "DeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "utils/CastOperator.hpp"


namespace sx
{
	class SwapchainVulkan
		: public ObjectWrapper<VkSwapchainKHR>
	{
	public:
		SwapchainVulkan(const VkDevice& device);
		virtual ~SwapchainVulkan();

		void Init(SurfaceVulkan& surface);
		uint32_t NumberOfImages();

	public:
		std::vector<VkImageView>& ImageViews();

	private:
		std::vector<VkImageView> swapChainImageViews;
		const VkDevice& device;
	};
}

#endif /* SWAPCHAIN_VULKAN_HPP */

