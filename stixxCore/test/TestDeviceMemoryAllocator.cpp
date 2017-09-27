#include <mocks/DeviceMemoryMock.hpp>
#include "../include/DeviceMemoryAllocator.hpp"

class DeviceMemoryControllerTest
    : public testing::Test
{
public:
    testing::StrictMock<DeviceMemoryMock> deviceMemory;
    sx::DeviceMemoryAllocator deviceMemoryController;
};

TEST(DeviceMemoryControllerInitTest, allocate_memory_on_init)
{

}


