#ifndef SHADER_VULKAN_HPP
#define SHADER_VULKAN_HPP

#include <vector>
#include "vulkan/vulkan.h"
#include "DeviceVulkan.hpp"
#include "CastOperator.hpp"

namespace sx
{
	class ShaderVulkan
		: public CastOperator<VkShaderModule>
	{
	public:
		ShaderVulkan(const VkDevice& device, VkShaderStageFlagBits shaderStageBits, const std::vector<uint32_t>& data);
		virtual ~ShaderVulkan();

		VkPipelineShaderStageCreateInfo GetConfiguration();

	private:
		VkDevice device;
		VkShaderStageFlagBits shaderStageFlagBits;
		VkShaderModuleCreateInfo shaderModuleCreateInfo;
	};

	class ShaderVertexVulkan
		: public ShaderVulkan
	{
	public:
		ShaderVertexVulkan(const VkDevice& device, const std::vector<uint32_t>& data);
	};

	class ShaderFragmentVulkan
		: public ShaderVulkan
	{
	public:
		ShaderFragmentVulkan(const VkDevice& device, const std::vector<uint32_t>& data);
	};

}
#endif
