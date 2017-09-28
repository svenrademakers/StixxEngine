#include <mocks/PhysicalDeviceMock.hpp>
#include <mocks/DeviceMock.hpp>
#include "../include/DeviceMemoryAllocator.hpp"

class DeviceMemoryControllerTest
    : public testing::Test
{
public:
    DeviceMemoryControllerTest()
        : deviceMemoryController(physicalDevice, device)
    {}

protected:
    testing::StrictMock<DeviceMock> device;
    testing::StrictMock<PhysicalDeviceMock> physicalDevice;
    sx::DeviceMemoryAllocator deviceMemoryController;
};

TEST_F(DeviceMemoryControllerTest, host_visible_heap_available)
{
    uint32_t handle;
    std::vector<sx::Heap> heaps;
    heaps.push_back({123, true, sx::Heap::HeapType::HostVisible});
    EXPECT_CALL(physicalDevice, HeapInfo()).WillOnce(testing::Return(heaps));
    EXPECT_CALL(device, CreateBuffer(sx::Device::TransportType::TransferSource, 256, testing::_)).WillOnce(::testing::SetArgReferee<2>(handle));
    deviceMemoryController.Configure();
}

//TEST_F(DeviceMemoryControllerTest, host_coherent_heap_available)
//{
//    uint32_t handle;
//    std::vector<sx::Heap> heaps;
//    heaps.push_back({123, true, sx::Heap::HeapType::HostCoherent});
//    EXPECT_CALL(physicalDevice, HeapInfo()).WillOnce(testing::Return(heaps));
//    EXPECT_CALL(device, CreateBuffer(sx::Device::TransportType::TransferSource, 256, testing::_)).WillOnce(::testing::SetArgReferee<2>(handle));
//    deviceMemoryController.Configure();
//}

TEST_F(DeviceMemoryControllerTest, return_runtime_error_no_usefull_memorytype)
{
    std::vector<sx::Heap> heaps;
    EXPECT_CALL(physicalDevice, HeapInfo()).WillOnce(testing::Return(heaps));
    EXPECT_THROW(deviceMemoryController.Configure(), std::runtime_error);

    heaps.push_back({123, true, sx::Heap::HeapType::DeviceLocal});
    EXPECT_CALL(physicalDevice, HeapInfo()).WillOnce(testing::Return(heaps));
    EXPECT_THROW(deviceMemoryController.Configure(), std::runtime_error);

    heaps.push_back({123, false, sx::Heap::HeapType::HostVisible});
    EXPECT_CALL(physicalDevice, HeapInfo()).WillOnce(testing::Return(heaps));
    EXPECT_THROW(deviceMemoryController.Configure(), std::runtime_error);
}


