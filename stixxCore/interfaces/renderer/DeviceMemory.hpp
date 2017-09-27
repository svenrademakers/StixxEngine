#ifndef DEVICE_MEMORY_HPP
#define DEVICE_MEMORY_HPP

#include <stdint.h>
#include <cstddef>
#include <vector>

namespace sx
{
    class DeviceMemory
    {
    public:
        enum HeapType
        {
            DeviceLocal = 0x1,
            HostVisible = 0x2,
            HostCoherent = 0x4,
            HostCached = 0x8,
            LazilyAllocated = 0x10
        };

        struct Heap
        {
            size_t size;
            bool local;
            uint32_t supportedTypes;
        };

    public:
        virtual std::vector<Heap> HeapInfo() = 0;
        virtual bool AllocateMemory(uint8_t heapId, std::size_t size) = 0;
    };

}
#endif