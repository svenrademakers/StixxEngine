#ifndef DEVICE
#define DEVICE

#include <cstdint>
namespace sx
{
    class Device
    {
    public:
        enum TransportType
        {
            TransferSource = 0x1,
            TransferDestination = 0x2,
            UniformTexel = 0x4,
            StorageTexel = 0x8,
            Uniform = 0x10,
            Storage = 0x20,
            Index = 0x40,
            Vertex = 0x80,
            Indirect = 0x100,
            MaxEnum = 0x7FFFFFFF
        };

        virtual ~Device() {};

        virtual void CreateBuffer(const TransportType type, const std::size_t, uint32_t& bufferHandle) = 0;
        virtual void Allocate(const std::size_t, const uint8_t heapIndex) = 0;
        virtual void BindBuffer(const uint32_t bufferHandle, uint32_t& memoryHandle) = 0;
        //virtual void MemoryRequirements(const uint32_t bufferHandle, std::size_t size, size_t alignment,  )
    };
}
#endif