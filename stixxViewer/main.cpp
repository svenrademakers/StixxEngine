#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include "MeshGL.hpp"
#include "ShaderGL.hpp"

#include "ShaderLoader.hpp"
#include "MeshLoaderAssimp.hpp"

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

static void LoadMesh(sxgraphics::Mesh& mesh)
{
    std::string path(R"(/Users/svenrademakers/opengl_game_engine/resources/cube.obj)");

    std::vector<sxgraphics::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<sxgraphics::Texture> textures;

    MeshLoaderAssimp loader(path);
    loader.Next(vertices, indices, textures);

    mesh.Vertices(vertices);
    mesh.Indices(indices);
    mesh.Textures(textures);
}

static void SetPerspective()
{
}

int main(void)
{
    InitGLFW();
    GLFWwindow* mainWindowHandle = CreateWindow();
    InitGLEW();

	sxgraphics::ShaderGL shader;
	LoadShaders(shader);

	sxgraphics::MeshGL mesh;
	LoadMesh(mesh);

	mesh.Load();
//	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDHT / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
//	glUniformMatrix4fv(glGetUniformLocation(shader.id, "projection"), 1, GL_FALSE, &projection[0][0]);

    while (!glfwWindowShouldClose(mainWindowHandle))
    {
     	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
     	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     	glm::mat4 modelTrans;
//     	modelTrans = glm::rotate(modelTrans, static_cast<float>(glfwGetTime()), glm::vec3(0.5f, 1.0f, 0.0f));
//        unsigned int modelLoc = glGetUniformLocation(shader.id, "model");
//        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrans));

     	shader.Use();
     	mesh.Draw(shader);

     	glfwSwapBuffers(mainWindowHandle);
        glfwPollEvents();
    }

    glfwDestroyWindow(mainWindowHandle);
    glfwTerminate();
    return EXIT_SUCCESS;
}

