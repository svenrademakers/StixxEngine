
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "WindowGlfw.hpp"
#include "RendererVulkan.hpp"

int main(void)
{
	static sx::WindowGlfw window("Hello Triangle", 800, 600);
	static sx::RendererVulkan vulcano(window);

	return 0;
}
