#include <sstream>
#include "WindowGlfw.hpp"
#include <GLFW/glfw3.h>

namespace
{
	static void error_callback(int error, const char* description)
	{
		std::ostringstream ss;
		ss << "error: " << error << " : " << description << std::endl;
		std::runtime_error(ss.str().c_str());
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

namespace sx
{
	WindowGlfw::WindowGlfw(const char * name, uint16_t width, uint16_t height)
		: name(name)
	{
		if (!glfwInit())
		{
			std::runtime_error("glfwInit returned false");
		}

		glfwSetErrorCallback(error_callback);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, name, nullptr, nullptr);
		if (!window)
		{
			glfwTerminate();
			std::runtime_error("Could not create window");
		}

		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);
	}	

	const char* WindowGlfw::Name()
	{
		return name;
	}
	
	bool WindowGlfw::ShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	std::vector<const char*> WindowGlfw::InstanceExtensions()
	{
		uint32_t count = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&count);
		
		if (glfwExtensions == nullptr)
			std::runtime_error("error retrieving Instance Extensions");

		std::vector<const char*> extensions;
		extensions.insert(extensions.end(), glfwExtensions, glfwExtensions + count);

		return extensions;
	}

	void WindowGlfw::Accept(WindowVisitor& renderer)
	{
		renderer.CreateSurface(*this);
	}

	GLFWwindow* WindowGlfw::GetHandle()
	{
		return window;
	}


}