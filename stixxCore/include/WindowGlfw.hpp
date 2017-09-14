#ifndef WINDOW_GLFW_HPP
#define WINDOW_GLFW_HPP

#include <GLFW/glfw3.h>
#include "Window.hpp"

namespace sx
{
	class WindowGlfw
		: public Window
	{
	public:
		WindowGlfw(const char * name, uint16_t width, uint16_t height);

		bool ShouldClose() override;

	private:
		GLFWwindow* window;
	};
}

#endif // 
