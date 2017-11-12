#ifndef UI_HANDLER_HPP
#define UI_HANDLER_HPP

#include "utils/Observer.hpp"

namespace sx
{
	enum MouseButton
	{
		Left = 0,
		Right = 1
	};

	enum ButtonState
	{
		Release = 0,
		Press = 1
	};

	class KeyboardObserver
		: public Observer<KeyboardObserver>
	{
	public:
		using Observer<KeyboardObserver>::Observer;

		virtual void KeyPressed(int key, ButtonState state) = 0;
	};

	class MouseObserver
		: public Observer<MouseObserver>
	{
	public:
		using Observer<MouseObserver>::Observer;

		virtual ~MouseObserver() {}
		virtual void MouseEvent(const MouseButton, ButtonState state) = 0;
		virtual void MouseMoved(double x, double y) = 0;
		virtual void Scroll(double xOffset, double yOffset) = 0;
	};
}

#endif