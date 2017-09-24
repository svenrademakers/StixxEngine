#ifndef SHADER_VULKAN_HPP
#define SHADER_VULKAN_HPP

#include <vector>

#include "DeviceVulkan.hpp"
#include "HandleExposer.hpp"

namespace sx
{
	class ShaderVulkan
		: HandleExposer<VkShaderModule>
	{
	public:
		ShaderVulkan(vk::Device& device, VkShaderStageFlagBits shaderStageBits, const std::vector<uint32_t>& data);
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
		ShaderVertexVulkan(vk::Device& device, const std::vector<uint32_t>& data);
	};

	class ShaderFragmentVulkan
		: public ShaderVulkan
	{
	public:
		ShaderFragmentVulkan(vk::Device& device, const std::vector<uint32_t>& data);
	};

}
#endif
