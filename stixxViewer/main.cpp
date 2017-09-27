#include <iostream>
#include "WindowGlfw.hpp"
#include "DeviceVulkan.hpp"
#include "InstanceVulkan.hpp"
#include "DeviceMemoryVulkan.hpp"
#include "SurfaceVulkan.hpp"

int main(void)
{
    static sx::WindowGlfw window("Hello Triangle", 800, 600);
    static sx::InstanceVulkan instance("stixxEngine", window.Name(), window.InstanceExtensions());
    static sx::SurfaceVulkan surface(instance);
    static sx::DeviceVulkan device(instance, surface);
    static sx::DeviceMemoryVulkan deviceMemoryVulkan(device, instance);

    return 0;
}
