#ifndef DEVICE_VULKAN_HPP
#define DEVICE_VULKAN_HPP

#include "vulkan/vulkan.h"
#include "CastOperator.hpp"

namespace sx
{
    class PhysicalDeviceVulkan;

	class DeviceVulkan
		: public CastOperator<VkDevice>
	{
	public:
		DeviceVulkan(PhysicalDeviceVulkan& pdevice);
        DeviceVulkan(const DeviceVulkan&) = delete;
        const DeviceVulkan& operator = (const DeviceVulkan&) = delete;
		virtual ~DeviceVulkan();

		const VkQueue& Queue();
		const VkCommandPool& CommandPool();

	private:
        PhysicalDeviceVulkan& pdevice;
		VkQueue queue;
		VkCommandPool commandPool;
	};
}

#endif /* DEVICE_VULKAN_HPP */
