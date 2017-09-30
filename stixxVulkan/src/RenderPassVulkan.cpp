#include "RenderPassVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include <stdexcept>

namespace sx
{
	RenderPassVulkan::RenderPassVulkan(const VkDevice &device)
		: device(device)
	{}

	RenderPassVulkan::~RenderPassVulkan()
	{
		for (size_t i = 0; i < frameBuffers.size(); i++) {
			vkDestroyFramebuffer(device, frameBuffers[i], nullptr);
		}

		vkDestroyRenderPass(device, handle, nullptr);
	}

	void RenderPassVulkan::Init(SwapchainVulkan &swapchain, SurfaceVulkan& surface)
	{
		VkAttachmentDescription colorAttachment = {};
		colorAttachment.format = static_cast<VkFormat>(surface.Format().first);
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef = {};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		VkSubpassDependency dependency = {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachment;
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &handle) != VK_SUCCESS)
			throw std::runtime_error("failed to create render pass!");

		frameBuffers.resize(swapchain.ImageViews().size());

		for (size_t i = 0; i < swapchain.ImageViews().size(); i++)
		{
			VkImageView attachments[] = { swapchain.ImageViews()[i]};
			VkFramebufferCreateInfo framebufferInfo = {};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = handle;
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.height = surface.CurrentExtent().height;
			framebufferInfo.width = surface.CurrentExtent().width;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &frameBuffers[i]) != VK_SUCCESS)
				throw std::runtime_error("failed to create framebuffer!");
		}
	}

	const std::vector<VkFramebuffer>& RenderPassVulkan::FrameBuffers()
	{
		return frameBuffers;
	}
}
