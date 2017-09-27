#include "gmock/gmock.h"
#include "renderer/DeviceMemory.hpp"


class DeviceMemoryMock
    : public sx::DeviceMemory
{
public:
    MOCK_METHOD1(AllocateMemory, bool(std::size_t));
    MOCK_METHOD0(Heaps, std::vector<sx::Heap>());
};