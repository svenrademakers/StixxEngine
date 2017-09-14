#include "RendererVulkan.hpp"

#include <vulkan\vulkan.h>
#include <GLFW/glfw3.h>

namespace
{
	VkInstance instance;
	VkSurfaceKHR surface;
	VkPhysicalDevice device;
}

namespace sx
{
	RendererVulkan::RendererVulkan(Window& window)
		: window(window)
	{
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = window.Name();
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "StixX";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		auto extensions = window.InstanceExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();
		createInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
			throw std::runtime_error("failed to create instance!");
		}

		window.Accept(*this);

		uint32_t deviceCount = 1;
		vkEnumeratePhysicalDevices(instance, &deviceCount, &device);

		if (device == nullptr) {
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}		
	}

	RendererVulkan::~RendererVulkan()
	{}
	
	void RendererVulkan::CreateSurface(WindowGlfw& windowGlfw) const
	{
		if (glfwCreateWindowSurface(instance, windowGlfw.GetHandle(), nullptr, &surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

	//void RendererVulkan::createLogicalDevice() 
	//{
	//	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

	//	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	//	std::set<int> uniqueQueueFamilies = { indices.graphicsFamily, indices.presentFamily };

	//	float queuePriority = 1.0f;
	//	for (int queueFamily : uniqueQueueFamilies) {
	//		VkDeviceQueueCreateInfo queueCreateInfo = {};
	//		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	//		queueCreateInfo.queueFamilyIndex = queueFamily;
	//		queueCreateInfo.queueCount = 1;
	//		queueCreateInfo.pQueuePriorities = &queuePriority;
	//		queueCreateInfos.push_back(queueCreateInfo);
	//	}

	//	VkPhysicalDeviceFeatures deviceFeatures = {};

	//	VkDeviceCreateInfo createInfo = {};
	//	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	//	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	//	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	//	createInfo.pEnabledFeatures = &deviceFeatures;

	//	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	//	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	//	if (enableValidationLayers) {
	//		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
	//		createInfo.ppEnabledLayerNames = validationLayers.data();
	//	}
	//	else {
	//		createInfo.enabledLayerCount = 0;
	//	}

	//	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
	//		throw std::runtime_error("failed to create logical device!");
	//	}

	//	vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphicsQueue);
	//	vkGetDeviceQueue(device, indices.presentFamily, 0, &presentQueue);
	//}

	//void RendererVulkan::createSwapChain() 
	//{
	//	SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

	//	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	//	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	//	VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

	//	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	//	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
	//		imageCount = swapChainSupport.capabilities.maxImageCount;
	//	}

	//	VkSwapchainCreateInfoKHR createInfo = {};
	//	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	//	createInfo.surface = surface;

	//	createInfo.minImageCount = imageCount;
	//	createInfo.imageFormat = surfaceFormat.format;
	//	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	//	createInfo.imageExtent = extent;
	//	createInfo.imageArrayLayers = 1;
	//	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	//	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
	//	uint32_t queueFamilyIndices[] = { (uint32_t)indices.graphicsFamily, (uint32_t)indices.presentFamily };

	//	if (indices.graphicsFamily != indices.presentFamily) {
	//		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
	//		createInfo.queueFamilyIndexCount = 2;
	//		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	//	}
	//	else {
	//		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	//	}

	//	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	//	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	//	createInfo.presentMode = presentMode;
	//	createInfo.clipped = VK_TRUE;

	//	createInfo.oldSwapchain = VK_NULL_HANDLE;

	//	if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
	//		throw std::runtime_error("failed to create swap chain!");
	//	}

	//	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
	//	swapChainImages.resize(imageCount);
	//	vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

	//	swapChainImageFormat = surfaceFormat.format;
	//	swapChainExtent = extent;
	//}

	//void RendererVulkan::createImageViews() 
	//{
	//	swapChainImageViews.resize(swapChainImages.size());

	//	for (size_t i = 0; i < swapChainImages.size(); i++) {
	//		VkImageViewCreateInfo createInfo = {};
	//		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	//		createInfo.image = swapChainImages[i];
	//		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	//		createInfo.format = swapChainImageFormat;
	//		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	//		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	//		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	//		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	//		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	//		createInfo.subresourceRange.baseMipLevel = 0;
	//		createInfo.subresourceRange.levelCount = 1;
	//		createInfo.subresourceRange.baseArrayLayer = 0;
	//		createInfo.subresourceRange.layerCount = 1;

	//		if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
	//			throw std::runtime_error("failed to create image views!");
	//		}
	//	}
	//}

	//void RendererVulkan::createRenderPass() 
	//{
	//	VkAttachmentDescription colorAttachment = {};
	//	colorAttachment.format = swapChainImageFormat;
	//	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	//	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	//	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	//	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	//	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	//	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	//	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	//	VkAttachmentReference colorAttachmentRef = {};
	//	colorAttachmentRef.attachment = 0;
	//	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	//	VkSubpassDescription subpass = {};
	//	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	//	subpass.colorAttachmentCount = 1;
	//	subpass.pColorAttachments = &colorAttachmentRef;

	//	VkSubpassDependency dependency = {};
	//	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	//	dependency.dstSubpass = 0;
	//	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	//	dependency.srcAccessMask = 0;
	//	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	//	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	//	VkRenderPassCreateInfo renderPassInfo = {};
	//	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	//	renderPassInfo.attachmentCount = 1;
	//	renderPassInfo.pAttachments = &colorAttachment;
	//	renderPassInfo.subpassCount = 1;
	//	renderPassInfo.pSubpasses = &subpass;
	//	renderPassInfo.dependencyCount = 1;
	//	renderPassInfo.pDependencies = &dependency;

	//	if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
	//		throw std::runtime_error("failed to create render pass!");
	//	}
	//}

	//void RendererVulkan::createGraphicsPipeline() 
	//{
	//	auto vertShaderCode = readFile("shaders/vert.spv");
	//	auto fragShaderCode = readFile("shaders/frag.spv");

	//	VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
	//	VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

	//	VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
	//	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	//	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	//	vertShaderStageInfo.module = vertShaderModule;
	//	vertShaderStageInfo.pName = "main";

	//	VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
	//	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	//	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	//	fragShaderStageInfo.module = fragShaderModule;
	//	fragShaderStageInfo.pName = "main";

	//	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	//	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
	//	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	//	vertexInputInfo.vertexBindingDescriptionCount = 0;
	//	vertexInputInfo.vertexAttributeDescriptionCount = 0;

	//	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	//	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	//	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	//	inputAssembly.primitiveRestartEnable = VK_FALSE;

	//	VkViewport viewport = {};
	//	viewport.x = 0.0f;
	//	viewport.y = 0.0f;
	//	viewport.width = (float)swapChainExtent.width;
	//	viewport.height = (float)swapChainExtent.height;
	//	viewport.minDepth = 0.0f;
	//	viewport.maxDepth = 1.0f;

	//	VkRect2D scissor = {};
	//	scissor.offset = { 0, 0 };
	//	scissor.extent = swapChainExtent;

	//	VkPipelineViewportStateCreateInfo viewportState = {};
	//	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	//	viewportState.viewportCount = 1;
	//	viewportState.pViewports = &viewport;
	//	viewportState.scissorCount = 1;
	//	viewportState.pScissors = &scissor;

	//	VkPipelineRasterizationStateCreateInfo rasterizer = {};
	//	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	//	rasterizer.depthClampEnable = VK_FALSE;
	//	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	//	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	//	rasterizer.lineWidth = 1.0f;
	//	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	//	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	//	rasterizer.depthBiasEnable = VK_FALSE;

	//	VkPipelineMultisampleStateCreateInfo multisampling = {};
	//	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	//	multisampling.sampleShadingEnable = VK_FALSE;
	//	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	//	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
	//	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	//	colorBlendAttachment.blendEnable = VK_FALSE;

	//	VkPipelineColorBlendStateCreateInfo colorBlending = {};
	//	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	//	colorBlending.logicOpEnable = VK_FALSE;
	//	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	//	colorBlending.attachmentCount = 1;
	//	colorBlending.pAttachments = &colorBlendAttachment;
	//	colorBlending.blendConstants[0] = 0.0f;
	//	colorBlending.blendConstants[1] = 0.0f;
	//	colorBlending.blendConstants[2] = 0.0f;
	//	colorBlending.blendConstants[3] = 0.0f;

	//	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	//	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	//	pipelineLayoutInfo.setLayoutCount = 0;
	//	pipelineLayoutInfo.pushConstantRangeCount = 0;

	//	if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
	//		throw std::runtime_error("failed to create pipeline layout!");
	//	}

	//	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	//	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	//	pipelineInfo.stageCount = 2;
	//	pipelineInfo.pStages = shaderStages;
	//	pipelineInfo.pVertexInputState = &vertexInputInfo;
	//	pipelineInfo.pInputAssemblyState = &inputAssembly;
	//	pipelineInfo.pViewportState = &viewportState;
	//	pipelineInfo.pRasterizationState = &rasterizer;
	//	pipelineInfo.pMultisampleState = &multisampling;
	//	pipelineInfo.pColorBlendState = &colorBlending;
	//	pipelineInfo.layout = pipelineLayout;
	//	pipelineInfo.renderPass = renderPass;
	//	pipelineInfo.subpass = 0;
	//	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	//	if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
	//		throw std::runtime_error("failed to create graphics pipeline!");
	//	}

	//	vkDestroyShaderModule(device, fragShaderModule, nullptr);
	//	vkDestroyShaderModule(device, vertShaderModule, nullptr);
	//}

	//void RendererVulkan::createFramebuffers() 
	//{
	//	swapChainFramebuffers.resize(swapChainImageViews.size());

	//	for (size_t i = 0; i < swapChainImageViews.size(); i++) {
	//		VkImageView attachments[] = {
	//			swapChainImageViews[i]
	//		};

	//		VkFramebufferCreateInfo framebufferInfo = {};
	//		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	//		framebufferInfo.renderPass = renderPass;
	//		framebufferInfo.attachmentCount = 1;
	//		framebufferInfo.pAttachments = attachments;
	//		framebufferInfo.width = swapChainExtent.width;
	//		framebufferInfo.height = swapChainExtent.height;
	//		framebufferInfo.layers = 1;

	//		if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
	//			throw std::runtime_error("failed to create framebuffer!");
	//		}
	//	}
	//}

	//void RendererVulkan::createCommandPool() 
	//{
	//	QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

	//	VkCommandPoolCreateInfo poolInfo = {};
	//	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	//	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;

	//	if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
	//		throw std::runtime_error("failed to create command pool!");
	//	}
	//}

	//void RendererVulkan::createCommandBuffers() 
	//{
	//	commandBuffers.resize(swapChainFramebuffers.size());

	//	VkCommandBufferAllocateInfo allocInfo = {};
	//	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	//	allocInfo.commandPool = commandPool;
	//	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	//	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	//	if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
	//		throw std::runtime_error("failed to allocate command buffers!");
	//	}

	//	for (size_t i = 0; i < commandBuffers.size(); i++) {
	//		VkCommandBufferBeginInfo beginInfo = {};
	//		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	//		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

	//		vkBeginCommandBuffer(commandBuffers[i], &beginInfo);

	//		VkRenderPassBeginInfo renderPassInfo = {};
	//		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	//		renderPassInfo.renderPass = renderPass;
	//		renderPassInfo.framebuffer = swapChainFramebuffers[i];
	//		renderPassInfo.renderArea.offset = { 0, 0 };
	//		renderPassInfo.renderArea.extent = swapChainExtent;

	//		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	//		renderPassInfo.clearValueCount = 1;
	//		renderPassInfo.pClearValues = &clearColor;

	//		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	//		vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

	//		vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

	//		vkCmdEndRenderPass(commandBuffers[i]);

	//		if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
	//			throw std::runtime_error("failed to record command buffer!");
	//		}
	//	}
	//}

	//void RendererVulkan::createSemaphores() 
	//{
	//	VkSemaphoreCreateInfo semaphoreInfo = {};
	//	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	//	if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
	//		vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS) {

	//		throw std::runtime_error("failed to create semaphores!");
	//	}
	//}

	void RendererVulkan::Draw()
	{

	}
}

