#ifndef DEVICE_VULKAN_HPP
#define DEVICE_VULKAN_HPP

#include "vulkan/vulkan.h"
#include "CastOperator.hpp"
#include "PhysicalDeviceVulkan.hpp"

namespace sx
{
    class InstanceVulkan;
    class SurfaceVulkan;

	class DeviceVulkan
		: public CastOperator<VkDevice>
	{
	public:
		DeviceVulkan(PhysicalDeviceVulkan& pdevice);
        DeviceVulkan(const DeviceVulkan&) = delete;
        const DeviceVulkan& operator = (const DeviceVulkan&) = delete;
		virtual ~DeviceVulkan();

		const VkQueue Queue();

	private:
        const VkPhysicalDevice& pdevice;
		VkQueue queue;
	};
}

#endif /* RENDERERVULKAN_HPP */
