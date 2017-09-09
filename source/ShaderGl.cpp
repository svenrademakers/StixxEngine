/*
 * ShaderGl.cpp
 *
 *  Created on: 9 Sep 2017
 *      Author: svenrademakers
 */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include "ShaderGl.h"

namespace
{
	void AbortOnError(GLuint shader)
	{
		int success;
		std::array<char, 512> buffer;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, buffer.size(), NULL, buffer.data());
			std::cerr << "Shader Compilation failed: \n" << buffer.data() << std::endl;
			std::abort();
		}
	}

	void AbortOnProgramError(GLuint program)
	{
		int success;
		std::array<char, 512> buffer;
	    glGetProgramiv(program, GL_LINK_STATUS, &success);
	    if (!success) {
	        glGetProgramInfoLog(program, buffer.size(), NULL, buffer.data());
	        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << buffer.data() << std::endl;
	        std::abort();
	    }
	}
}

void ShaderGl::Load(ShaderProvider& provider)
{
	const char* vertexSource = provider.VertexShader();
	const char* fragmentSource = provider.FragmentShader();

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	AbortOnError(vertex);

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);
	AbortOnError(fragment);

	// shader Program
	id = glCreateProgram();
	glAttachShader(*id, vertex);
	glAttachShader(*id, fragment);
	glLinkProgram(*id);
	AbortOnProgramError(*id);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
