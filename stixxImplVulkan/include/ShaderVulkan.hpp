#ifndef SHADER_VULKAN_HPP
#define SHADER_VULKAN_HPP

#include <vector>
#include <vulkan\vulkan.hpp>

namespace sx
{
	class ShaderVulkan
	{
	public:
		ShaderVulkan(const VkDevice& device, VkShaderStageFlagBits shaderStageBits, const std::vector<uint32_t>& data);
		ShaderVulkan(const ShaderVulkan&) = delete;
		ShaderVulkan& operator= (const ShaderVulkan&) = delete;
		virtual ~ShaderVulkan();

		VkPipelineShaderStageCreateInfo GetConfiguration();

	private:
		const VkDevice& device;
		VkShaderStageFlagBits shaderStageFlagBits;
		VkShaderModuleCreateInfo shaderModuleCreateInfo;
		VkShaderModule shaderModule;
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