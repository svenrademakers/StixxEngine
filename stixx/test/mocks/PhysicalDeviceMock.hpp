#include "gmock/gmock.h"
#include "renderer/PhysicalDevice.hpp"

class PhysicalDeviceMock
    : public sx::PhysicalDevice
{
public:
    MOCK_METHOD2(AllocateMemory, bool(uint8_t, std::size_t));
    MOCK_METHOD0(HeapInfo, std::vector<sx::Heap>());
};