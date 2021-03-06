/*
 * ShaderGL.cpp
 *
 *  Created on: 9 Sep 2017
 *      Author: svenrademakers
 */

#include <iostream>
#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderGL.hpp"
#include "ShaderLoader.hpp"

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
	        std::cerr << "Shader Program Linking failed\n" << buffer.data() << std::endl;
	        std::abort();
	    }
	}

}

namespace sxgraphics
{
	void ShaderGL::Load(ShaderRaw& vertexData, ShaderRaw& fragmentData)
	{
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, vertexData.Shader(), NULL);
		glCompileShader(vertex);
		AbortOnError(vertex);

		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, fragmentData.Shader(), NULL);
		glCompileShader(fragment);
		AbortOnError(fragment);

		// shader Program
		id = glCreateProgram();
		glAttachShader(id, vertex);
		glAttachShader(id, fragment);
		glLinkProgram(id);
		AbortOnProgramError(id);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void ShaderGL::Use()
	{
		glUseProgram(id);
	}
}
