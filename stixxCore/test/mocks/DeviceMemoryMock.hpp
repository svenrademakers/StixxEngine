#include "gmock/gmock.h"
#include "renderer/DeviceMemory.hpp"


class DeviceMemoryMock
    : public sx::DeviceMemory
{
public:
    MOCK_METHOD2(AllocateMemory, bool(uint8_t, std::size_t));
    MOCK_METHOD0(HeapInfo, std::vector<sx::DeviceMemory::Heap>());
};