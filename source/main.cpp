#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "MeshGL.hpp"
#include "ShaderGL.hpp"

#include "ShaderLoader.hpp"

#define WINDOW_WIDHT 800
#define WINDOW_HEIGHT 600

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

static void LoadShaders(sxgraphics::Shader& shader)
{
    std::string path(R"(/Users/svenrademakers/opengl_game_engine/source/shaders/)");
    std::string vertex(path + "main.shdr");
    std::string fragment(path + "fragment.shdr");

    sxgraphics::ShaderDataLoader fragmentFile(fragment);
    sxgraphics::ShaderDataLoader vertexFile(vertex);

    shader.Load(vertexFile, fragmentFile);
}

static unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

int main(void)
{
    InitGLFW();
    GLFWwindow* mainWindowHandle = CreateWindow();
    InitGLEW();

	sxgraphics::ShaderGL shader;
	LoadShaders(shader);

	std::vector<sxgraphics::Vertex> vertices;

	sxgraphics::Vertex topr;
	topr.Position =  {0.5f,  0.5f, 0.0f};
	vertices.push_back(topr);

	topr.Position =  { 0.5f, -0.5f, 0.0f};
	vertices.push_back(topr);

	topr.Position =  {-0.5f, -0.5f, 0.0f};
	vertices.push_back(topr);

	topr.Position =  {-0.5f,  0.5f, 0.0f};
	vertices.push_back(topr);

	std::vector<GLuint> indicesCol(std::begin(indices), std::end(indices));
	std::vector<sxgraphics::Texture> textures;

	static sxgraphics::MeshGL cube(vertices, indicesCol, textures);

    while (!glfwWindowShouldClose(mainWindowHandle))
    {
     	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
     	glClear(GL_COLOR_BUFFER_BIT);

     	shader.Use();
     	cube.Draw(shader);

     	glfwSwapBuffers(mainWindowHandle);
        glfwPollEvents();
    }

    glfwDestroyWindow(mainWindowHandle);
    glfwTerminate();
    return EXIT_SUCCESS;
}

