#include "ShaderVulkan.hpp"
#include <stdexcept>

namespace sx
{
	ShaderVertexVulkan::ShaderVertexVulkan(const VkDevice& device, FileSystem& filesystem)
		: ShaderVulkan(device, filesystem, "vert.spv")
	{}

	ShaderFragmentVulkan::ShaderFragmentVulkan(const VkDevice& device, FileSystem& filesystem)
		: ShaderVulkan(device, filesystem, "frag.spv")
	{}
}
