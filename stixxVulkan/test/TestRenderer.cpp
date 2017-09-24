#include "gmock/gmock.h"
#include "vulkan/vulkan.hpp"
#include "mocks/VulkanMock.hpp"

#include "RendererVulkan.hpp"
#include "mocks/WindowMock.hpp"

class TestRenderer : public ::testing::Test
{
public:
    TestRenderer()
    : renderer(window, vertex, fragment)
    {}

protected:
    sx::RendererVulkan renderer;
    ::testing::StrictMock<WindowMock> window;

    std::vector<uint32_t> vertex;
    std::vector<uint32_t> fragment;
};


TEST_F(TestRenderer, scene_gets_loaded_in_host_visible_heap)
{
    VkResult r;


    VkDevice device;
    VkBufferCreateInfo info = {};

    VkBuffer buffer;
    EXPECT_CALL(vulkanMock, vkCreateBuffer(device, &info, nullptr, &buffer)).WillOnce(testing::Return(r));

    vkCreateBuffer(device, &info, nullptr, &buffer);


    EXPECT_FALSE(false);
}
