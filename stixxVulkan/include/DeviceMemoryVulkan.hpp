#include "vulkan/vulkan.h"
#include "renderer/DeviceMemory.hpp"

namespace sx
{
    class DeviceMemoryVulkan
            : public DeviceMemory
    {
    public:
        DeviceMemoryVulkan(const VkDevice device, const VkPhysicalDevice pdevice);
        DeviceMemoryVulkan(const DeviceMemoryVulkan&) = delete;
        DeviceMemoryVulkan& operator= (const DeviceMemoryVulkan&) = delete;

        virtual std::vector<Heap> Heaps() override;
        virtual bool AllocateMemory(std::size_t size) override;

    private:
        const VkDevice device;
        const VkPhysicalDevice pdevice;
    };
}