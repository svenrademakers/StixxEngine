#include <iostream>
#include <vulkan/vulkan.hpp>
#include "WindowGlfw.hpp"
#include "FileSystem.hpp"
#include "RendererVulkan.hpp"
#include "MeshLoaderAssimp.hpp"

int main(void)
{
    std::vector<sx::Vertex> vertex;
    std::vector<uint32_t> indices;
    std::vector<sx::Texture> texture;
    static MeshLoaderAssimp meshLoader("/home/sven/stixx/examples/aap.obj");
    meshLoader.Next(vertex, indices, texture);

    static sx::FileSystemStd fileSystem;
    static sx::WindowGlfw window("Hello Triangle", 800, 600);

    static sx::RendererVulkan renderer(window, fileSystem.LoadFile("/home/sven/stixx/stixxShaders/vert.spv"), fileSystem.LoadFile("/home/sven/stixx/stixxShaders/frag.spv"));

    while (!window.ShouldClose()) {
        window.Poll();
        renderer.Draw();
    }

    return 0;
}
