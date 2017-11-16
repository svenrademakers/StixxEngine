#include "InputGlfw.hpp"
#include <thread> 
#include "WindowGlfw.hpp" 

namespace
{
	sx::InputGlfw* instance;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		instance->NotifyObservers([key, action](sx::KeyboardObserver& ob) {
			ob.KeyPressed(key, static_cast<sx::ButtonState>(action));
		});
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		instance->NotifyObservers([xpos, ypos](sx::MouseObserver& ob) {
			ob.MouseMoved(xpos, ypos);
		});
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		instance->NotifyObservers([button, action](sx::MouseObserver& ob) {
			ob.MouseEvent(static_cast<sx::MouseButton>(button), static_cast<sx::ButtonState>(action));
		});
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		instance->NotifyObservers([xoffset, yoffset](sx::MouseObserver& ob) {
			ob.Scroll(xoffset, yoffset);
		});
	}
}

namespace sx
{
	InputGlfw::InputGlfw(Window& window)
		: WindowObserver(window)
	{}

	void InputGlfw::WindowCreated(WindowHandle& handle)
	{
		Attach(handle);
	}

	void InputGlfw::Attach(WindowHandle& handle)
	{
		instance = this;
		//glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetInputMode(handle, GLFW_STICKY_KEYS, 1);
		glfwSetKeyCallback(handle, key_callback);
		glfwSetCursorPosCallback(handle, cursor_position_callback);
		glfwSetMouseButtonCallback(handle, mouse_button_callback);
		glfwSetScrollCallback(handle, scroll_callback);
	}

	void InputGlfw::Closing()
	{}
}