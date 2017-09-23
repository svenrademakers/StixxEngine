#include "SwapchainVulkan.hpp"
#include <stdexcept>

namespace sx
{
	SwapchainVulkan::~SwapchainVulkan()
	{
		for (size_t i = 0; i < swapChainImageViews.size(); i++) {
			vkDestroyImageView(device, swapChainImageViews[i], nullptr);
		}

		vkDestroySwapchainKHR(device, handle, nullptr);
	}

	void SwapchainVulkan::Init(vk::Device& device, SurfaceVulkan&  surface)
	{
        this->device = device;
		VkSwapchainCreateInfoKHR SwapchainInfo = {};
		SwapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		SwapchainInfo.surface = *surface;
		SwapchainInfo.minImageCount = surface.ImageCount();
		SwapchainInfo.imageFormat = surface.Format();
		SwapchainInfo.imageColorSpace = surface.ColorSpace();
		SwapchainInfo.imageExtent = surface.Extent();
		SwapchainInfo.imageArrayLayers = 1;
		SwapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		SwapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; //VK_SHARING_MODE_CONCURRENT
		SwapchainInfo.preTransform = surface.CurrentTransform();
		SwapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		SwapchainInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
		SwapchainInfo.clipped = VK_TRUE;
		SwapchainInfo.oldSwapchain = VK_NULL_HANDLE;


		if (vkCreateSwapchainKHR(device, &SwapchainInfo, nullptr, &handle) != VK_SUCCESS)
			throw std::runtime_error("failed to create swap chain!");

		uint32_t imageCount;
		std::vector<VkImage> swapChainImages;
		vkGetSwapchainImagesKHR(device, handle, &imageCount, nullptr);
		swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(device, handle, &imageCount, swapChainImages.data());

		swapChainImageViews.resize(imageCount);

		for (auto it = swapChainImageViews.begin(); it != swapChainImageViews.end(); it++)
		{
			VkImageViewCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = swapChainImages[std::distance(swapChainImageViews.begin(), it)];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = SwapchainInfo.imageFormat;
			createInfo.components = { VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY,VK_COMPONENT_SWIZZLE_IDENTITY };
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(device, &createInfo, nullptr, &*it) != VK_SUCCESS)
				throw std::runtime_error("failed to create image views!");
		}

		format = surface.Format();
		extent = surface.Extent();
	}


	std::vector<VkImageView>& SwapchainVulkan::ImageViews()
	{
		return swapChainImageViews;
	}

	VkFormat SwapchainVulkan::Format()
	{
		return format;
	}

	VkExtent2D SwapchainVulkan::Extent()
	{
		return extent;
	}
}
