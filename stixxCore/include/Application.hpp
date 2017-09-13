#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include "Observer.hpp"

namespace sx
{
	class KeyBoardObserver
		: public Observer
	{
	public:
		using Observer::Observer;
	};

	class Application
	{
	public:
		virtual ~Application(){};
		virtual void Load()  = 0;
	};
}

#endif /* SHADERLOADER_HPP_ */
