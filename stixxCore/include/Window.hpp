#ifndef WINDOW_HPP
#define WINDOW_HPP

namespace sx
{
	class Window
	{
	public:
		virtual ~Window() {};
		virtual bool ShouldClose() = 0;
	};
}

#endif /* SHADERLOADER_HPP_ */
