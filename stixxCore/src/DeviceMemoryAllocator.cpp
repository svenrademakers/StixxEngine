#include "DeviceMemoryAllocator.hpp"
#include <algorithm>
#include <stdexcept>

#define STAGING_BUFFER_SIZE 256
namespace sx
{
    DeviceMemoryAllocator::DeviceMemoryAllocator(PhysicalDevice& physicalDevice, Device& device)
            : physicalDevice(physicalDevice)
            , device(device)
    { }

    void DeviceMemoryAllocator::Configure()
    {
        std::vector<Heap> heaps = physicalDevice.HeapInfo();
        auto heap = std::find_if(heaps.begin(), heaps.end(), [](Heap& heap){
            return heap.local &&((heap.heapType &= Heap::HeapType::HostVisible)
                                 || (heap.heapType &= Heap::HeapType::HostCoherent));
        });

        if (heap == heaps.end())
            throw std::runtime_error("need host visible memory");

        device.CreateBuffer(Device::TransportType::TransferSource, STAGING_BUFFER_SIZE, stagingBufferHandle);
    }
}