#include "gmock/gmock.h"
#include "vulkan/vulkan.hpp"
#include "mocks/VulkanMock.hpp"

#include "RendererVulkan.hpp"

class TestRenderer : public ::testing::Test
{
protected:

};


TEST_F(TestRenderer, hoi)
{
    VkResult r;


    VkDevice device;
    VkBufferCreateInfo info = {};

    VkBuffer buffer;
    EXPECT_CALL(vulkanMock, vkCreateBuffer(device, &info, nullptr, &buffer)).WillOnce(testing::Return(r));

    vkCreateBuffer(device, &info, nullptr, &buffer);


    EXPECT_FALSE(false);
}
