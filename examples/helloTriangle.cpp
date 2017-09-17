#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "InstanceVulkan.hpp"
#include "WindowGlfw.hpp"
#include "SurfaceVulkan.hpp"
#include "DeviceVulkan.hpp"
#include "SwapchainVulkan.hpp"
#include "RenderPassVulkan.hpp"
#include "PipelineVulkan.hpp"
#include "FileSystem.hpp"
#include "RendererVulkan.hpp"

int main(void)
{
	static sx::FileSystemStd fileSystem;

	static sx::WindowGlfw window("Hello Triangle", 800, 600);
	static sx::InstanceVulkan instance("stixx", "Hello Triangle", window.InstanceExtensions());
	static sx::SurfaceVulkan surface(instance, *window.GetHandle());
	static sx::DeviceVulkan device(instance, surface);

	static sx::SwapchainVulkan swapchain(device, surface);
	static sx::RenderPassVulkan renderpass(device, swapchain);

	static sx::PipelineVulkan pipeline(device, renderpass, surface, fileSystem.LoadFile("vertex.spv"), fileSystem.LoadFile("fragment.spv"));
	static sx::RendererVulkan renderer(device, pipeline, renderpass, swapchain);

	//renderer.Draw();

	return 0;
}
