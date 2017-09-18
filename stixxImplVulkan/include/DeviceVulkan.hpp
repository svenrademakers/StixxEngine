#ifndef DEVICE_VULKAN_HPP
#define DEVICE_VULKAN_HPP

#include "InstanceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "HandleExposer.hpp"

namespace sx
{
	typedef std::pair<uint32_t, const VkQueue&> QueuePair;

	class DeviceVulkan
		: public HandleExposer<VkDevice>
	{
	public:
		DeviceVulkan(InstanceVulkan& instance, SurfaceVulkan& surface);
		virtual ~DeviceVulkan();

		QueuePair GraphicsQueue();
		QueuePair PresentQueue();

	private:
		uint32_t GetGraphicsFamilyIndex(const VkPhysicalDevice& device) const;

	private:
		VkQueue graphicsQueue;
		VkQueue presentQueue;

		uint32_t queueFamilyIndex;
	};
}

#endif /* RENDERERVULKAN_HPP */
