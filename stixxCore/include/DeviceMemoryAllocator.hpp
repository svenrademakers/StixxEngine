#ifndef DEVICE_MEMORY_CONTROLLER_HPP
#define DEVICE_MEMORY_CONTROLLER_HPP

#include "renderer/PhysicalDevice.hpp"
#include "renderer/Device.hpp"

namespace sx
{
    class DeviceMemoryAllocator
    {
    public:
        DeviceMemoryAllocator(PhysicalDevice &physicalDevice, Device& device);
        DeviceMemoryAllocator(const DeviceMemoryAllocator&) = delete;
        const DeviceMemoryAllocator& operator = (const DeviceMemoryAllocator&) = delete;

        void Configure();

    private:
        Device& device;
        PhysicalDevice& physicalDevice;
        uint32_t stagingBufferHandle;
    };
}

#endif