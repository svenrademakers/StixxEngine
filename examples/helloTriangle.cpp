#include <iostream>
#include <vulkan/vulkan.hpp>
#include "WindowGlfw.hpp"
#include "FileSystem.hpp"
#include "RendererVulkan.hpp"

int main(void)
{
    try {
        static sx::FileSystemStd fileSystem;
        static sx::WindowGlfw window("Hello Triangle", 800, 600);
        static sx::RendererVulkan renderer(window, fileSystem.LoadFile("/home/sven/stixx/stixxShaders/vert.spv"), fileSystem.LoadFile("/home/sven/stixx/stixxShaders/frag.spv"));

        while (!window.ShouldClose()) {
            window.Poll();
            renderer.Draw();
        }
    }
    catch(std::runtime_error err)
    {
        std::cerr << err.what();
    }

	return 0;
}
