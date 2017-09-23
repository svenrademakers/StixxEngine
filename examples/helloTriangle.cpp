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
	static sx::RendererVulkan renderer(window, fileSystem.LoadFile(""), fileSystem.LoadFile(""));



	while (!window.ShouldClose())
	{
		window.Poll();
		renderer.Draw();
	}

	return 0;
}
