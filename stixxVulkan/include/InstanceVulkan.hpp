#ifndef INSTANCE_VULKAN_HPP
#define INSTANCE_VULKAN_HPP

#include <vector>
#include "vulkan/vulkan.h"
#include "utils/CastOperator.hpp"

namespace sx
{
    class Window;

	class InstanceVulkan
        : public CastOperator<VkInstance>
	{
	public:
		InstanceVulkan(const char* engineName, const char* appName, std::vector<const char*> instanceExtensions);
        InstanceVulkan(const InstanceVulkan& instance) = delete;
        const InstanceVulkan& operator = (const InstanceVulkan&) = delete;
		virtual ~InstanceVulkan();

	private:
		VkDebugReportCallbackEXT callback;
	};
}

#endif /* INSTANCE_VULKAN_HPP */
