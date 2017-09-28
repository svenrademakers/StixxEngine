#ifndef PHYSICAL_DEVICE_HPP
#define PHYSICAL_DEVICE_HPP
#include <cstdio>
#include <cstdint>
#include <vector>

namespace sx
{
    class Device;

    struct Heap
    {
        enum HeapType
        {
            DeviceLocal = 0x1,
            HostVisible = 0x2,
            HostCoherent = 0x4,
            HostCached = 0x8,
            LazilyAllocated = 0x10
        };

        std::size_t size;
        bool local;
        uint32_t heapType;
    };

    class PhysicalDevice
    {
    public:
        virtual ~PhysicalDevice() {};
        virtual std::vector<Heap> HeapInfo() = 0;
        virtual bool AllocateMemory(uint8_t heapId, std::size_t size) = 0;
    };
}

#endif