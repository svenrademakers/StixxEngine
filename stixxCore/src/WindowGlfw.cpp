#include <sstream>
#include "WindowGlfw.hpp"
#include <stdexcept>
#include <thread>

namespace
{
	static void error_callback(int error, const char* description)
	{
		std::ostringstream ss;
		ss << "error: " << error << " : " << description << std::endl;
		std::runtime_error(ss.str().c_str());
	}
}

namespace sx
{
	WindowGlfw::WindowGlfw(const char * name, uint16_t width, uint16_t height)
		: window()
		, name(name)
		, width(width)
		, height(height)
	{
		if (!glfwInit())
			throw std::runtime_error("glfwInit returned false");
	}

	WindowGlfw::~WindowGlfw()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	const char* WindowGlfw::Name()
	{
		return name;
	}

	bool WindowGlfw::IsOpen()
	{
		return !glfwWindowShouldClose(window);
	}

	WindowHandle& WindowGlfw::GetHandle()
	{
		return window;
	}

    std::pair<uint32_t, uint32_t> WindowGlfw::Size()
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        return {width, height};
    }

	void WindowGlfw::Close()
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	void WindowGlfw::Run()
	{
		std::thread worker([this]() {
			glfwSetErrorCallback(error_callback);
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

			window = glfwCreateWindow(width, height, name, nullptr, nullptr);
			if (window == nullptr)
				glfwTerminate();

			NotifyObservers([this](sx::WindowObserver& observer) {
				observer.WindowCreated(window);
			});

			while (IsOpen())
				glfwWaitEvents();

			NotifyObservers([this](sx::WindowObserver& observer) {
				observer.Closing();
			});
		});

		worker.detach();
	}

	std::vector<const char*> WindowGlfw::InstanceExtensions()
	{
		uint32_t count = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&count);

		if (glfwExtensions == nullptr || count == 0)
			throw std::runtime_error("error retrieving Instance Extensions");

		std::vector<const char*> extensions;
		extensions.insert(extensions.end(), glfwExtensions, glfwExtensions + count);
		return extensions;
	}
}
