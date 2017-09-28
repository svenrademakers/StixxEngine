#include "vulkan/vulkan.h"
#include "renderer/DeviceMemory.hpp"

namespace sx
{
    class DeviceMemoryVulkan
            : public DeviceMemory
    {
    public:
        DeviceMemoryVulkan(const VkDevice& device, const VkPhysicalDevice& pdevice);
        DeviceMemoryVulkan(const DeviceMemoryVulkan&) = delete;
        DeviceMemoryVulkan& operator= (const DeviceMemoryVulkan&) = delete;

        virtual std::vector<Heap> HeapInfo() override;
        virtual bool AllocateMemory(uint8_t heapId, std::size_t size) override;

    private:
        const VkDevice& device;
        const VkPhysicalDevice& pdevice;
    };
}