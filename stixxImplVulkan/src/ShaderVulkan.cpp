#include "ShaderVulkan.hpp"
namespace sx
{
	ShaderFragmentVulkan::ShaderFragmentVulkan(const VkDevice& device, const std::vector<uint32_t>& data)
		: ShaderVulkan(device, VK_SHADER_STAGE_FRAGMENT_BIT, data)
	{}

	ShaderVertexVulkan::ShaderVertexVulkan(const VkDevice& device, const std::vector<uint32_t>& data)
		: ShaderVulkan(device, VK_SHADER_STAGE_VERTEX_BIT, data)
	{}

	ShaderVulkan::ShaderVulkan(const VkDevice& device, VkShaderStageFlagBits shaderStageFlagBits, const std::vector<uint32_t>& data)
		: device(device)
		, shaderStageFlagBits(shaderStageFlagBits)
	{
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCreateInfo.codeSize = data.size();
		shaderModuleCreateInfo.pCode = data.data();

		if (vkCreateShaderModule(device, &shaderModuleCreateInfo, nullptr, &shaderModule) != VK_SUCCESS)
			throw std::runtime_error("failed to create shader module!");
	}

	ShaderVulkan::~ShaderVulkan()
	{
		vkDestroyShaderModule(device, shaderModule, nullptr);
	}

	VkPipelineShaderStageCreateInfo ShaderVulkan::GetConfiguration()
	{
		VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo = {};
		pipelineShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		pipelineShaderStageCreateInfo.stage = shaderStageFlagBits;
		pipelineShaderStageCreateInfo.module = shaderModule;
		pipelineShaderStageCreateInfo.pName = "main";

		return pipelineShaderStageCreateInfo;
	}
}