#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include "utils/Observer.hpp"

namespace sx
{
	class WindowHandle;

	class WindowObserver
		: public Observer<WindowObserver>
	{
	public:
		using Observer<WindowObserver>::Observer;

		virtual void WindowCreated(WindowHandle& handle) = 0;
	};

	class Window
		: public Subject<WindowObserver>
	{
	public:
		using Extent = std::pair<uint32_t, uint32_t>;
		virtual ~Window() {};

		virtual const char* Name() = 0;
		virtual bool IsOpen() = 0;
		virtual void Close() = 0;
		virtual void Run() = 0;
		virtual Extent Size() = 0;
		virtual WindowHandle& GetHandle() = 0;
	};
}

#endif /* WINDOW_HPP */
