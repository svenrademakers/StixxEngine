#ifndef DEVICE_MEMORY_CONTROLLER_HPP
#define DEVICE_MEMORY_CONTROLLER_HPP

#include "renderer/DeviceMemory.hpp"

namespace sx
{
    class DeviceMemoryAllocator
    {
    public:
        DeviceMemoryAllocator(DeviceMemory &deviceMemory);

    private:
        DeviceMemory &deviceMemory;
    };
}

#endif