#ifndef UIHANDLER_GLFW_HPP
#define UIHANDLER_GLFW_HPP

#include <atomic>
#include "UiHandler.hpp"

struct GLFWwindow;

namespace sx
{
	class UiHandlerGlfw
		: public Subject<KeyboardObserver>
		, public Subject<MouseObserver>
	{
	public:
		UiHandlerGlfw(GLFWwindow* window);
	};
}

#endif