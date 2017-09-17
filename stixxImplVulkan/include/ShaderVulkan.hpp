#ifndef SHADER_VULKAN_HPP
#define SHADER_VULKAN_HPP

#include <vector>
#include <vulkan\vulkan.hpp>
#include "DeviceVulkan.hpp"
namespace sx
{
	class ShaderVulkan
	{
	public:
		ShaderVulkan(DeviceVulkan& device, VkShaderStageFlagBits shaderStageBits, const std::vector<uint32_t>& data);
		ShaderVulkan(const ShaderVulkan&) = delete;
		ShaderVulkan& operator= (const ShaderVulkan&) = delete;
		virtual ~ShaderVulkan();

		VkPipelineShaderStageCreateInfo GetConfiguration();

	private:
		DeviceVulkan& device;
		VkShaderStageFlagBits shaderStageFlagBits;
		VkShaderModuleCreateInfo shaderModuleCreateInfo;
		VkShaderModule shaderModule;
	};

	class ShaderVertexVulkan
		: public ShaderVulkan
	{
	public:
		ShaderVertexVulkan(DeviceVulkan& device, const std::vector<uint32_t>& data);
	};

	class ShaderFragmentVulkan
		: public ShaderVulkan
	{
	public:
		ShaderFragmentVulkan(DeviceVulkan& device, const std::vector<uint32_t>& data);
	};

}
#endif