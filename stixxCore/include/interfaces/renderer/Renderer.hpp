#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <chrono>
#include "utils/Observer.hpp"

namespace sx
{
	class HotLoopObserver
		: public Observer<HotLoopObserver>
	{
	public:
		using Observer<HotLoopObserver>::Observer;
		virtual void Update(std::chrono::duration<float>& elapsedMs) = 0;
	};

	class Renderer
		: public Subject<HotLoopObserver>
	{
	public:
		virtual ~Renderer(){};
		virtual void Draw()  = 0;
	};
}

#endif
