#ifndef INPUT_GLFW_HPP
#define INPUT_GLFW_HPP

#include <atomic>
#include "Input.hpp"
#include "Window.hpp"

namespace sx
{
	class InputGlfw
		: public Input
		, public WindowObserver
	{
	public:
		InputGlfw(Window& window);
		virtual void WindowCreated(WindowHandle& handle) override;
		virtual void Closing() override;

	private:
		void Attach(WindowHandle& handle) override;
	};
}

#endif