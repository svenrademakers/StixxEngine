#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// order matters! vulkan incl before glfw
#include "RendererVulkan.hpp"
#include "WindowGlfw.hpp"
#include "FileSystem.hpp"

int main(void)
{
	static sx::FileSystemStd fileSystem;
	static sx::WindowGlfw window("Hello Triangle", 800, 600);
	static sx::RendererVulkan renderer(window, fileSystem.LoadFile("vertex.spv"), fileSystem.LoadFile("fragment.spv"));

	renderer.Draw();

	return 0;
}
