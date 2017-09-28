#include <iostream>
#include <stdexcept>
#include "WindowGlfw.hpp"
#include "DeviceVulkan.hpp"
#include "InstanceVulkan.hpp"
#include "SurfaceVulkan.hpp"

int main(void)
{
    static sx::WindowGlfw window("Hello Triangle", 800, 600);
    static sx::InstanceVulkan instance("stixxEngine", window.Name(), window.InstanceExtensions());
    static sx::SurfaceVulkan surface(instance);
    if (!surface.CreateSurface(window))
        throw std::runtime_error("not able to create window");

    static sx::DeviceVulkan device(instance, surface);

    return 0;
}
