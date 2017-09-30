#include  <stdexcept>
#include "InstanceVulkan.hpp"
#include "Window.hpp"
#include <stdexcept>
#include <iostream>
#include <cstring>

namespace
{
	const std::vector<const char*> validationLayers = {
			"VK_LAYER_LUNARG_standard_validation"
	};

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
	{
		std::cerr << "validation layer: " << msg << std::endl;

		return VK_FALSE;
	}

	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		} else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}
}

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

        auto extension = window.InstanceExtensions();
        extension.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

		VkInstanceCreateInfo InstanceInfo = {};
		InstanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		InstanceInfo.pApplicationInfo = &appInfo;
		InstanceInfo.enabledExtensionCount = static_cast<uint32_t>(extension.size());
		InstanceInfo.ppEnabledExtensionNames = extension.data();
		InstanceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());;
		InstanceInfo.ppEnabledLayerNames = validationLayers.data();

		if(vkCreateInstance(&InstanceInfo, nullptr, &handle) != VK_SUCCESS)
			throw std::runtime_error("failed to create instance.");


		VkDebugReportCallbackCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		createInfo.pfnCallback = debugCallback;

		if (CreateDebugReportCallbackEXT(handle, &createInfo, nullptr, &callback) != VK_SUCCESS) {
			throw std::runtime_error("failed to set up debug callback!");
		}
    }

	InstanceVulkan::~InstanceVulkan()
	{
		DestroyDebugReportCallbackEXT(handle, callback, nullptr);
		vkDestroyInstance(handle, nullptr);
	}
}

