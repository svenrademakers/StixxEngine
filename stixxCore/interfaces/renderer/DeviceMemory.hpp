#ifndef DEVICE_MEMORY_HPP
#define DEVICE_MEMORY_HPP

#include <stdint.h>
#include <cstddef>
#include <vector>

namespace sx
{
    enum HeapType
    {
        HostVisible,
        DeviceVisible
    };

    struct Heap
    {
        uint32_t id;
        HeapType type;
    };

    class DeviceMemory
    {
    public:
        virtual std::vector<Heap> Heaps() = 0;
        virtual bool AllocateMemory(std::size_t size) = 0;
    };

}
#endif