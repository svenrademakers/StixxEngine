#ifndef INSTANCE_VULKAN_HPP
#define INSTANCE_VULKAN_HPP

#include <vector>
#include "vulkan/vulkan.h"

namespace sx
{
	class InstanceVulkan
	{
	public:
		InstanceVulkan(const char* engineName, const char* windowName, const std::vector<const char*>& extensions);
        InstanceVulkan(const InstanceVulkan& instance) = delete;
        const InstanceVulkan& operator = (const InstanceVulkan&) = delete;
		virtual ~InstanceVulkan();

		operator const VkInstance&() const;
        operator const VkPhysicalDevice&() const;


	private:
		VkPhysicalDevice physicalDevice;
        VkInstance instance;
	};
}

#endif /* INSTANCE_VULKAN_HPP */
