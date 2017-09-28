#include "gmock/gmock.h"
#include "renderer/Device.hpp"


class DeviceMock
    : public sx::Device
{
public:
    MOCK_METHOD3(CreateBuffer, void(const TransportType type, const std::size_t, uint32_t& bufferHandle));
    MOCK_METHOD2(Allocate, void(const std::size_t, const uint8_t heapIndex));
    MOCK_METHOD2(BindBuffer, void(const uint32_t buffer, uint32_t& memoryHandle));
};