#ifndef SHADER_VULKAN_HPP
#define SHADER_VULKAN_HPP

#include <vector>
#include <vulkan\vulkan.hpp>
#include "DeviceVulkan.hpp"
#include "HandleExposer.hpp"

namespace sx
{
	class ShaderVulkan
		: HandleExposer<VkShaderModule>
	{
	public:
		ShaderVulkan(DeviceVulkan& device, VkShaderStageFlagBits shaderStageBits, const std::vector<char>& data);
		virtual ~ShaderVulkan();

		VkPipelineShaderStageCreateInfo GetConfiguration();

	private:
		DeviceVulkan& device;
		VkShaderStageFlagBits shaderStageFlagBits;
		VkShaderModuleCreateInfo shaderModuleCreateInfo;
	};

	class ShaderVertexVulkan
		: public ShaderVulkan
	{
	public:
		ShaderVertexVulkan(DeviceVulkan& device, const std::vector<char>& data);
	};

	class ShaderFragmentVulkan
		: public ShaderVulkan
	{
	public:
		ShaderFragmentVulkan(DeviceVulkan& device, const std::vector<char>& data);
	};

}
#endif