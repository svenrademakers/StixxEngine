#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// order matters! vulkan incl before glfw
#include "RendererVulkan.hpp"
#include "WindowGlfw.hpp"

int main(void)
{
	static sx::WindowGlfw window("Hello Triangle", 800, 600);
	static sx::RendererVulkan renderer(window);

	renderer.Draw();

	return 0;
}
