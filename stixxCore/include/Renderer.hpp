#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>

namespace sx
{
	class WindowGlfw;

	class WindowVisitor
	{
	public:
		virtual void CreateSurface(WindowGlfw& window) const = 0;
	};

	class Renderer
		: public WindowVisitor
	{
	public:
		virtual ~Renderer(){};
		virtual void Draw()  = 0;
	};
}

#endif /* RENDERER_HPP */
