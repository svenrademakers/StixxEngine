#ifndef INSTANCE_VULKAN_HPP
#define INSTANCE_VULKAN_HPP

#include <vector>
#include "vulkan\vulkan.h"
#include "HandleExposer.hpp"

namespace sx
{
	class InstanceVulkan
		: public HandleExposer<VkInstance>
	{
	public:
		InstanceVulkan::InstanceVulkan(const char* engineName, const char* windowName, const std::vector<const char*>& extensions);
		virtual ~InstanceVulkan();

	public:
		const VkPhysicalDevice& PhysicalDevice();
		
	private:
		VkPhysicalDevice physicalDevice;
	};
}

#endif /* INSTANCE_VULKAN_HPP */
