#ifndef WINDOW_GLFW_HPP
#define WINDOW_GLFW_HPP

#include <atomic>
#include <GLFW/glfw3.h>
#include "interfaces/Window.hpp"
#include "utils/CastOperator.hpp"

namespace sx
{
	class WindowHandle
		: public CastOperator<GLFWwindow*>
	{
	public:
		WindowHandle& operator=(GLFWwindow* w)
		{
			handle = w;
			return *this;
		}
	};

	class WindowGlfw
		: public Window
	{
	public:
		WindowGlfw(const char * name, uint16_t width, uint16_t height);
		virtual ~WindowGlfw();

		// Window
		const char* Name() override;
		bool IsOpen() override;
		void Close() override;
		void Run() override;
		WindowHandle& GetHandle() override;
		Extent Size() override;

		static std::vector<const char*> InstanceExtensions();

	private:
		WindowHandle window;
		const char* name;
		uint16_t width;
		uint16_t height;
	};
}

#endif
