#include  <stdexcept>
#include "InstanceVulkan.hpp"
#include "Window.hpp"
#include <stdexcept>

namespace sx
{
	InstanceVulkan::InstanceVulkan(const char* engineName, Window& window)
	{
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = window.Name();
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = engineName;
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo InstanceInfo = {};
		InstanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		InstanceInfo.pApplicationInfo = &appInfo;
		InstanceInfo.enabledExtensionCount = static_cast<uint32_t>(window.InstanceExtensions().size());
		InstanceInfo.ppEnabledExtensionNames = window.InstanceExtensions().data();
		InstanceInfo.enabledLayerCount = 0;
        if (vkCreateInstance(&InstanceInfo, nullptr, &handle) != VK_SUCCESS)
			throw std::runtime_error("failed to create instance.");
	}

	InstanceVulkan::~InstanceVulkan()
	{
		vkDestroyInstance(handle, nullptr);
	}
}

