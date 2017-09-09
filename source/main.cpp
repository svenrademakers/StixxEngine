#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderGl.h"
#include "GameContainerMac.h"

#define WINDOW_WIDHT 800
#define WINDOW_HEIGHT 600

class ShaderProviderDummy
	: public ShaderProvider
{
public:
	const char* VertexShader() const override
	{

		return "#version 330 core\n"
			    "layout (location = 0) in vec3 aPos;\n"
			    "void main()\n"
			    "{\n"
			    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			    "}\0";
	}

	const char* FragmentShader() const override
	{
		return "#version 330 core\n"
			    "out vec4 FragColor;\n"
			    "void main()\n"
			    "{\n"
			    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			    "}\n\0";
	}
};

static void error_callback(int error, const char* description)
{
    std::cerr << "error: " << error << " : " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

static GLFWwindow* CreateWindow()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDHT, WINDOW_HEIGHT, "Svens Awsome Game", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cerr << "Window Error" << std::endl;
		std::abort();
	}

	glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    return window;
}

static void InitGLEW()
{
    glewExperimental=true;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        std::abort();
    }
}

static void InitGLFW()
{
    if (!glfwInit())
    {
        std::cerr << "glfwInit returned false" << std::endl;
        std::abort();
    }
    
    glfwSetErrorCallback(error_callback);
}

int main(void)
{
    InitGLFW();
    GLFWwindow* mainWindowHandle = CreateWindow();
    InitGLEW();

	static ShaderProviderDummy dummy;
	static ShaderGl myFirstShader;
	myFirstShader.Load(dummy);

    while (!glfwWindowShouldClose(mainWindowHandle))
    {
     	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
     	glClear(GL_COLOR_BUFFER_BIT);

     	//TODO

     	glfwSwapBuffers(mainWindowHandle);
        glfwPollEvents();
    }

    glfwDestroyWindow(mainWindowHandle);
    glfwTerminate();
    return EXIT_SUCCESS;
}

