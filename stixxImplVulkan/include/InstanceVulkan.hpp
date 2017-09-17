#ifndef INSTANCE_VULKAN_HPP
#define INSTANCE_VULKAN_HPP

#include <vector>
#include "vulkan\vulkan.h"

namespace sx
{
	class InstanceVulkan
	{
	public:
		InstanceVulkan::InstanceVulkan(const char* engineName, const char* windowName, const std::vector<const char*>& extensions);
		InstanceVulkan(const InstanceVulkan&) = delete;
		InstanceVulkan& operator = (const InstanceVulkan&) = delete;
		virtual ~InstanceVulkan();

	public:
		const VkInstance& Instance();
		const VkPhysicalDevice& PhysicalDevice();
		
	private:
		VkInstance instance;		
		VkPhysicalDevice physicalDevice;
	};
}

#endif /* INSTANCE_VULKAN_HPP */
