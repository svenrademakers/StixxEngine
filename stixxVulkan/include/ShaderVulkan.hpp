#ifndef SHADER_VULKAN_HPP
#define SHADER_VULKAN_HPP

#include <vector>
#include <sstream>
#include <array>
#include "vulkan/vulkan.h"
#include "DeviceVulkan.hpp"
#include "CastOperator.hpp"
#include "FileSystem.hpp"

#define SHADER_PATH "../StixxShaders"

namespace sx
{
	template<VkShaderStageFlagBits shaderStageBit>
	class ShaderVulkan
		: public CastOperator<VkShaderModule>
	{
	public:
		constexpr ShaderVulkan(const VkDevice& device, FileSystem& filesystem, const char * name);
		virtual ~ShaderVulkan();

		constexpr VkPipelineShaderStageCreateInfo GetConfiguration();

	private:
		const VkDevice& device;
		const char * name;
	};

	class ShaderVertexVulkan
		: public ShaderVulkan<VK_SHADER_STAGE_VERTEX_BIT>
	{
	public:
		ShaderVertexVulkan(const VkDevice& device, FileSystem& filesystem);
		const VkPipelineVertexInputStateCreateInfo* VertexBindings() const;

	private:
		VkPipelineVertexInputStateCreateInfo vertexInputInfo;
		std::array<VkVertexInputBindingDescription, 1> vertexInputBindingDescription;
		std::array<VkVertexInputAttributeDescription, 1> vertexInputAttributeDescriptions;
	};

	class ShaderFragmentVulkan
		: public ShaderVulkan<VK_SHADER_STAGE_FRAGMENT_BIT>
	{
	public:
		ShaderFragmentVulkan(const VkDevice& device, FileSystem& filesystem);
	};

	template<VkShaderStageFlagBits shaderStageBit>
	constexpr ShaderVulkan<shaderStageBit>::ShaderVulkan(const VkDevice& device, FileSystem& filesystem, const char* name)
		: device(device)
		, name(name)
	{
		std::stringstream fileName;
		fileName << SHADER_PATH << "/" << name;

		const std::vector<uint32_t> data = filesystem.LoadFile(fileName.str().c_str());

		VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCreateInfo.pNext = nullptr;
		shaderModuleCreateInfo.flags = 0;
		shaderModuleCreateInfo.codeSize = data.size();
		shaderModuleCreateInfo.pCode = data.data();

		if (vkCreateShaderModule(device, &shaderModuleCreateInfo, nullptr, &handle) != VK_SUCCESS)
			throw std::runtime_error("failed to create shader module!");
	}

	template<VkShaderStageFlagBits shaderStageBit>
	ShaderVulkan<shaderStageBit>::~ShaderVulkan()
	{
		vkDestroyShaderModule(device, handle, nullptr);
	}

	template<VkShaderStageFlagBits shaderStageBit>
	constexpr VkPipelineShaderStageCreateInfo ShaderVulkan<shaderStageBit>::GetConfiguration()
	{
		VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo = {};
		pipelineShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		pipelineShaderStageCreateInfo.stage = shaderStageBit;
		pipelineShaderStageCreateInfo.module = handle;
		pipelineShaderStageCreateInfo.pName = name;

		return pipelineShaderStageCreateInfo;
	}

}
#endif
