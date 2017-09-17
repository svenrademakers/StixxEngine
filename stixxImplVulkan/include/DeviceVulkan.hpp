#ifndef DEVICE_VULKAN_HPP
#define DEVICE_VULKAN_HPP

#include "InstanceVulkan.hpp"
#include "SurfaceVulkan.hpp"

namespace sx
{
	class DeviceVulkan
	{
	public:
		DeviceVulkan(InstanceVulkan& instance, SurfaceVulkan& surface);
		DeviceVulkan(const DeviceVulkan&) = delete;
		DeviceVulkan& operator = (const DeviceVulkan&) = delete;
		virtual ~DeviceVulkan();

		const VkDevice& Device();

	private:
		VkDeviceQueueCreateInfo CreateGraphicsQueue(const VkPhysicalDevice& device) const;


	private:
		VkDevice device;
		VkQueue graphicsQueue;

	};
}

#endif /* RENDERERVULKAN_HPP */
