#include "PipelineVulkan.hpp"
#include <stdexcept>
#include <Mesh.hpp>
#include <array>

namespace
{
	VkExtent2D Extent(sx::Surface::Extent ex)
	{
		VkExtent2D extent;
		extent.width = ex.width;
		extent.height = ex.height;

		return extent;
	}
}
namespace sx
{
	PipelineVulkan::PipelineVulkan(const VkDevice &device)
		: device(device)
	{}

	PipelineVulkan::~PipelineVulkan()
	{
		vkDestroyPipeline(device, handle, nullptr);
		vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
	}

	void PipelineVulkan::Init(RenderPassVulkan& renderpass, SurfaceVulkan& surface, ShaderVertexVulkan& vertex, ShaderFragmentVulkan& fragment, VkViewport& viewport)
	{
		VkPipelineShaderStageCreateInfo shaderStages[] = { vertex.GetConfiguration(), fragment.GetConfiguration() };

		std::array<VkVertexInputBindingDescription, 1> vertexInputBindingDescription = {};
		vertexInputBindingDescription[0].binding = 0;
		vertexInputBindingDescription[0].stride = sizeof(sx::Vertex);
		vertexInputBindingDescription[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		std::array<VkVertexInputAttributeDescription, 1> vertexInputAttributeDescriptions;
		vertexInputAttributeDescriptions[0].binding = 0;
		vertexInputAttributeDescriptions[0].location = 0;
		vertexInputAttributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		vertexInputAttributeDescriptions[0].offset = offsetof(sx::Vertex, Normal);

//		vertexInputAttributeDescriptions[1].binding = 0;
//		vertexInputAttributeDescriptions[1].location = 1;
//		vertexInputAttributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
//		vertexInputAttributeDescriptions[1].offset = offsetof(sx::Vertex, color);

		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexAttributeDescriptionCount = vertexInputAttributeDescriptions.size();
		vertexInputInfo.pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data();
		vertexInputInfo.pVertexBindingDescriptions = vertexInputBindingDescription.data();
        vertexInputInfo.vertexBindingDescriptionCount = vertexInputBindingDescription.size();

		VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkRect2D scissor = {};
		scissor.offset = { 0, 0 };
		scissor.extent = Extent(surface.CurrentExtent());
		VkPipelineViewportStateCreateInfo viewportState = {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;

		VkPipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;

		VkPipelineColorBlendStateCreateInfo colorBlending = {};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pushConstantRangeCount = 0;

		if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
			throw std::runtime_error("failed to create pipeline layout!");

		VkGraphicsPipelineCreateInfo pipelineInfo = {};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.layout = pipelineLayout;
		pipelineInfo.renderPass = renderpass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		auto result = vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &handle);
		if (result != VK_SUCCESS)
			throw std::runtime_error("failed to create graphics pipeline!");
	}
}
