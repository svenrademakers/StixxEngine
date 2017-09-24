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
		virtual ~WindowGlfw();

		const char* Name() override;
		bool ShouldClose() override;
		void Poll();
		std::vector<const char*> InstanceExtensions() override;
		std::pair<uint32_t, uint32_t> Size() override;

		GLFWwindow* GetHandle();
	private:
		GLFWwindow* window;
		const char* name;
	};
}

#endif // 
