#ifndef INPUT_INTERACTOR_HPP
#define INPUT_INTERACTOR_HPP

#include "interfaces/Input.hpp"

namespace sx
{
	class Window;

	class InputInteractor
		: public KeyboardObserver
		, public MouseObserver
	{
	public:
		InputInteractor(Subject<KeyboardObserver>& keyboardSubject, Subject<MouseObserver>& mouseSubject, Window& window);

		void KeyPressed(int key, ButtonState state) override;
		void MouseEvent(const MouseButton button, ButtonState state) override;
		void MouseMoved(double x, double y) override;
		void Scroll(double xOffset, double yOffset) override;

	private:
		Window& window;
	};
}

#endif