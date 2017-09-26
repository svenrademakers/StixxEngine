#include "vulkan/vulkan.hpp"
#include "gmock/gmock.h"

class VulkanMock
{
public:
    MOCK_METHOD3(vkCreateInstance, VkResult(const VkInstanceCreateInfo*, const VkAllocationCallbacks*, VkInstance*));
    MOCK_METHOD4(vkCreateBuffer, VkResult(VkDevice, const VkBufferCreateInfo*, const VkAllocationCallbacks*, VkBuffer*));
    MOCK_METHOD3(vkEnumeratePhysicalDevices, VkResult(VkInstance, uint32_t*, VkPhysicalDevice*));
    MOCK_METHOD2(vkDestroyInstance, VkResult(VkInstance,const VkAllocationCallbacks*));
};

static VulkanMock* vulkanHook = nullptr;

VkResult vkCreateBuffer(
        VkDevice                                    device,
        const VkBufferCreateInfo*                   pCreateInfo,
        const VkAllocationCallbacks*                pAllocator,
        VkBuffer*                                   pBuffer)
{
    vulkanHook->vkCreateBuffer(device, pCreateInfo, pAllocator, pBuffer);
}

VkResult VKAPI_CALL vkCreateInstance(
        const VkInstanceCreateInfo*                 pCreateInfo,
        const VkAllocationCallbacks*                pAllocator,
        VkInstance*                                 pInstance)
{
    vulkanHook->vkCreateInstance(pCreateInfo, pAllocator, pInstance);
}

VkResult vkEnumeratePhysicalDevices(
        VkInstance                                  instance,
        uint32_t*                                   pPhysicalDeviceCount,
        VkPhysicalDevice*                           pPhysicalDevices)
{
    vulkanHook->vkEnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices);
}

VKAPI_ATTR void VKAPI_CALL vkDestroyInstance(
        VkInstance                                  instance,
        const VkAllocationCallbacks*                pAllocator)
{
    vulkanHook->vkDestroyInstance(instance, pAllocator);
}