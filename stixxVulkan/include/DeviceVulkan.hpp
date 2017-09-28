#ifndef DEVICE_VULKAN_HPP
#define DEVICE_VULKAN_HPP

#include "vulkan/vulkan.h"
#include "renderer/Device.hpp"

namespace sx
{
    class InstanceVulkan;
    class SurfaceVulkan;

	class DeviceVulkan
	{
	public:
		DeviceVulkan(const InstanceVulkan& instance, const SurfaceVulkan& surface);
        DeviceVulkan(const DeviceVulkan&) = delete;
        const DeviceVulkan& operator = (const DeviceVulkan&) = delete;
		virtual ~DeviceVulkan();

        operator const VkDevice&() const;

	private:
		uint32_t GetGraphicsFamilyIndex(const VkPhysicalDevice& device);

	private:
        VkDevice device;
		VkQueue graphicsQueue;
		VkQueue presentQueue;
        VkQueue TransferQueu;

        uint32_t queueFamilyIndex;
	};
}

#endif /* RENDERERVULKAN_HPP */
