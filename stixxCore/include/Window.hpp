#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include "Renderer.hpp"

namespace sx
{
	class WindowVisitor;

	class Window
	{
	public:
		virtual ~Window() {};

		virtual const char* Name() = 0;
		virtual bool ShouldClose() = 0;
		virtual std::vector<const char*> InstanceExtensions() = 0;
		virtual void Accept(WindowVisitor& visitor) = 0;
	};
}

#endif /* SHADERLOADER_HPP_ */
