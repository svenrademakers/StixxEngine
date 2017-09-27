#include "DeviceMemoryAllocator.hpp"

namespace sx
{
    DeviceMemoryAllocator::DeviceMemoryAllocator(DeviceMemory &deviceMemory)
            : deviceMemory(deviceMemory)
    {}
}