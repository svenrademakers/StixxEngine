#ifndef RENDERER_HPP
#define RENDERER_HPP

namespace sx
{
	class Renderer
	{
	public:
		virtual ~Renderer(){};
		virtual void Draw()  = 0;
	};
}

#endif
