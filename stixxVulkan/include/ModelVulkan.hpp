#ifndef MODEL_VULKAN_HPP
#define MODEL_VULKAN_HPP

#include <stdexcept>
#include "DeviceVulkan.hpp"
#include "PhysicalDeviceVulkan.hpp"
#include "Mesh.hpp"

namespace sx
{
	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

	class ModelVulkan
	{
	public:
		ModelVulkan(const VkDevice& device, const VkPhysicalDevice& pdevice, const sx::Mesh& mesh);
		virtual ~ModelVulkan();

		void Draw(const VkCommandBuffer& drawCmdBuffer);

	private:
		template<VkBufferUsageFlags flags>
		void LoadBuffer(VkBuffer& buffer, const std::size_t size) const
		{
			VkBufferCreateInfo bufferInfo = {};
			bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size = size;
			bufferInfo.flags = 0;
			bufferInfo.usage = flags;
			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			bufferInfo.queueFamilyIndexCount = 0;
			bufferInfo.pQueueFamilyIndices = 0;
			vkCreateBuffer(device, &bufferInfo, nullptr, &buffer);

			if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
				throw std::runtime_error("failed to create buffer!");
			}
		}

		VkDeviceMemory AttachMemory(VkBuffer& buffer) const;
		void LoadVertexData(const Mesh& mesh);

	private:
		const VkDevice& device;
		const VkPhysicalDevice& pdevice;

		const std::size_t vertexSize;
		const std::uint32_t indicesCount;
		const std::size_t indexSize;

		VkBuffer buffer;
		VkBuffer uboBuffer;
		VkDeviceMemory deviceMemory;
		VkDeviceMemory uboMemory;

		UniformBufferObject ubo;
	};
}
#endif