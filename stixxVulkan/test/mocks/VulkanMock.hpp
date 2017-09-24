#include "vulkan/vulkan.hpp"
#include "gmock/gmock.h"

class VulkanMock
{
public:
    MOCK_METHOD3(vkCreateInstance, VkResult(const VkInstanceCreateInfo*, const VkAllocationCallbacks*, VkInstance*));
    MOCK_METHOD4(vkCreateBuffer, VkResult(VkDevice, const VkBufferCreateInfo*, const VkAllocationCallbacks*, VkBuffer*));
};

static VulkanMock vulkanMock;

VkResult vkCreateBuffer(
        VkDevice                                    device,
        const VkBufferCreateInfo*                   pCreateInfo,
        const VkAllocationCallbacks*                pAllocator,
        VkBuffer*                                   pBuffer)
{
    vulkanMock.vkCreateBuffer(device, pCreateInfo, pAllocator, pBuffer);
}

VkResult VKAPI_CALL vkCreateInstance(
        const VkInstanceCreateInfo*                 pCreateInfo,
        const VkAllocationCallbacks*                pAllocator,
        VkInstance*                                 pInstance)
{
    vulkanMock.vkCreateInstance(pCreateInfo, pAllocator, pInstance);
}