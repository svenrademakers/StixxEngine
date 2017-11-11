#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>
#include "Mesh.hpp"

namespace sx
{
	class Renderer
	{
	public:
		virtual ~Renderer(){};
		virtual void Draw()  = 0;
		virtual void Load() = 0;
	};
}

#endif /* RENDERER_HPP */
