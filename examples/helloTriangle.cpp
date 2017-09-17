#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "InstanceVulkan.hpp"
#include "WindowGlfw.hpp"
#include "SurfaceVulkan.hpp"
#include "DeviceVulkan.hpp"
#include "RenderPassVulkan.hpp"
#include "PipelineVulkan.hpp"
#include "FileSystem.hpp"

int main(void)
{
	static sx::FileSystemStd fileSystem;
	static sx::WindowGlfw window("Hello Triangle", 800, 600);

	static sx::InstanceVulkan instance("stixx", "Hello Triangle", window.InstanceExtensions());
	static sx::SurfaceVulkan surface(instance, *window.GetHandle());

	static sx::DeviceVulkan device(instance, surface);
	auto deviceHandle = device.Device();
	//static sx::RenderPassVulkan renderpass(deviceHandle, surface.Format());
	//static sx::RenderPassVulkan)

	//static sx::RenderPassVulkan renderPass(device, surface.)
	//static sx::PipelineVulkan(device.Device(), renderPass)

	//static sx::RendererVulkan renderer(window, fileSystem.LoadFile("vertex.spv"), fileSystem.LoadFile("fragment.spv"));

	//renderer.Draw();

	return 0;
}
