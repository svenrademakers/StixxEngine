#include "ShaderVulkan.hpp"
#include <stdexcept>
#include "renderer/Mesh.hpp"

namespace sx
{
	ShaderVertexVulkan::ShaderVertexVulkan(const VkDevice& device, FileSystem& filesystem)
		: ShaderVulkan(device, filesystem, "vert.spv")
	{
		vertexInputBindingDescription[0].binding = 0;
		vertexInputBindingDescription[0].stride = sizeof(sx::Vertex);
		vertexInputBindingDescription[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		vertexInputAttributeDescriptions[0].binding = 0;
		vertexInputAttributeDescriptions[0].location = 0;
		vertexInputAttributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		vertexInputAttributeDescriptions[0].offset = offsetof(sx::Vertex, Normal);

		//		vertexInputAttributeDescriptions[1].binding = 0;
		//		vertexInputAttributeDescriptions[1].location = 1;
		//		vertexInputAttributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		//		vertexInputAttributeDescriptions[1].offset = offsetof(sx::Vertex, color);

		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributeDescriptions.size());
		vertexInputInfo.pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data();
		vertexInputInfo.pVertexBindingDescriptions = vertexInputBindingDescription.data();
		vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexInputBindingDescription.size());

		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorCount = 1;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.pImmutableSamplers = nullptr;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		descriptorLayout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorLayout.bindingCount = 1;
		descriptorLayout.pBindings = &uboLayoutBinding;
	}

	ShaderFragmentVulkan::ShaderFragmentVulkan(const VkDevice& device, FileSystem& filesystem)
		: ShaderVulkan(device, filesystem, "frag.spv")
	{}
}
