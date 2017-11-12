#include "UiHandlerGlfw.hpp"
#include <thread> 
#include "GLFW/glfw3.h"

namespace
{
	sx::UiHandlerGlfw* instance;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		static_cast<sx::Subject<sx::KeyboardObserver>*>(instance)->NotifyObservers([key, action](sx::KeyboardObserver& ob) {
			ob.KeyPressed(key, static_cast<sx::ButtonState>(action));
		});
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		static_cast<sx::Subject<sx::MouseObserver>*>(instance)->NotifyObservers([xpos, ypos](sx::MouseObserver& ob) {
			ob.MouseMoved(xpos, ypos);
		});
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		static_cast<sx::Subject<sx::MouseObserver>*>(instance)->NotifyObservers([button, action](sx::MouseObserver& ob) {
			ob.MouseEvent(static_cast<sx::MouseButton>(button), static_cast<sx::ButtonState>(action));
		});
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		static_cast<sx::Subject<sx::MouseObserver>*>(instance)->NotifyObservers([xoffset, yoffset](sx::MouseObserver& ob) {
			ob.Scroll(xoffset, yoffset);
		});
	}
}

namespace sx
{
	UiHandlerGlfw::UiHandlerGlfw(GLFWwindow* window)
	{
		instance = this;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetScrollCallback(window, scroll_callback);
	}

}