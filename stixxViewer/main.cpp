#include <iostream>
#include "InstanceVulkan.hpp"
#include "WindowGlfw.hpp"
#include "FileSystem.hpp"
#include "RendererVulkan.hpp"
#include "MeshLoaderAssimp.hpp"
#include "PhysicalDeviceVulkan.hpp"
#include "DeviceVulkan.hpp"
#include "DeviceMemoryAllocatorVulkan.hpp"

int main(void)
{
//    std::vector<uint32_t> indices;
//    std::vector<sx::Texture> texture;
//    //static MeshLoaderAssimp meshLoader("/home/sven/Documents/Stixx/examples/cube.obj");
//    //meshLoader.Next(vertices, indices, texture);
//
    sx::Mesh mesh;
    sx::Vertex vertex = {};
    vertex.Normal = {-0.5f,-0.5f,-0.7};
    mesh.vertices.push_back(vertex);
    vertex.Normal = {0.5,-0.5,0.3};
    mesh.vertices.push_back(vertex);
    vertex.Normal = {0.5,0.5,0.0};
    mesh.vertices.push_back(vertex);
    vertex.Normal = {-0.5f, 0.5f, 0.0};
    mesh.vertices.push_back(vertex);
    mesh.indices = {0,1,2,2,3,0};

    std::vector<uint32_t> data(reinterpret_cast<uint32_t*>(&mesh), reinterpret_cast<uint32_t*>(&mesh +1));


    static sx::FileSystemStd fileSystem;

    static sx::WindowGlfw window("Hello Triangle", 800, 600);
    static sx::InstanceVulkan instance("Stixx", window);
    static sx::PhysicalDeviceVulkan pdevice(instance);
    static sx::SurfaceVulkan surface(instance, pdevice);
    if (!surface.CreateSurface(window) || !pdevice.PresentSupport(surface))
        throw std::runtime_error("could not setup surface");

    static sx::DeviceVulkan device(pdevice);
    static sx::RendererVulkan renderer(pdevice, device, surface,
                                       fileSystem.LoadFile("../stixxShaders/vert.spv"),
                                       fileSystem.LoadFile("../stixxShaders/frag.spv"));

	sx::ModelVulkan model(device, pdevice, mesh);
	renderer.RecordDrawingCommands(model);

    while (!window.ShouldClose()) {
        window.Poll();
        renderer.Draw();
    }

    return 0;
}