#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>

namespace sx
{
	class Renderer
	{
	public:
		virtual ~Renderer(){};
		virtual void Draw()  = 0;
	};
}

#endif /* RENDERER_HPP */
