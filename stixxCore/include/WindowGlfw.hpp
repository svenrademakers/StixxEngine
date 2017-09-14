#ifndef WINDOW_GLFW_HPP
#define WINDOW_GLFW_HPP

#include "Window.hpp"

struct GLFWwindow;

namespace sx
{
	class WindowGlfw
		: public Window
	{
	public:
		WindowGlfw(const char * name, uint16_t width, uint16_t height);

		const char* Name() override;
		bool ShouldClose() override;
		std::vector<const char*> InstanceExtensions() override;
		void Accept(WindowVisitor& renderer) override;

		GLFWwindow* GetHandle();
	private:
		GLFWwindow* window;
		const char* name;
	};
}

#endif // 
