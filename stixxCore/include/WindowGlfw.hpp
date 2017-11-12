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

		// Window
		const char* Name() override;
		bool Open() override;
		std::vector<const char*> InstanceExtensions() override;
		std::pair<uint32_t, uint32_t> Size() override;
		void Close() override;
		void* GetHandle();

	private:
		GLFWwindow* window;
		const char* name;
	};
}

#endif // 
