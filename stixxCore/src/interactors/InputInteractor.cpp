#include "interactors/InputInteractor.hpp"
#include "interfaces/Window.hpp"
#include "interfaces/Camera.hpp"
#include <iostream>

namespace sx
{
	InputInteractor::InputInteractor(Subject<KeyboardObserver>& keyboardSubject, Subject<MouseObserver>& mouseSubject, Window& window)
		: KeyboardObserver(keyboardSubject)
		, MouseObserver(mouseSubject)
		, window(window)
	{}

	void InputInteractor::KeyPressed(int key, ButtonState state)
	{
		std::cout << "key pressed " << key << ": " << (state == Press ? "Pressed" : "Released") << "\n";
	}

	void InputInteractor::MouseEvent(const MouseButton button, ButtonState state)
	{
		std::cout << "Mouse pressed " << (button == Left ? "Left" : "Right") << ": " << (state == Press ? "Pressed" : "Released") << "\n";
	}

	void InputInteractor::MouseMoved(double x, double y)
	{
		std::cout << "Mouse moved x:" << x << " y: " << y << "\n";
	}

	void InputInteractor::Scroll(double xOffset, double yOffset)
	{
		std::cout << "Scroll x:" << xOffset << " y: " << yOffset << "\n";
	}
}