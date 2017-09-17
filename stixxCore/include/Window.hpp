#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>

namespace sx
{
	class Window
	{
	public:
		virtual ~Window() {};

		virtual const char* Name() = 0;
		virtual bool ShouldClose() = 0;

		virtual std::vector<const char*> InstanceExtensions() = 0;
	};
}

#endif /* SHADERLOADER_HPP_ */
