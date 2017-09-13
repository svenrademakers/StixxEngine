/*
 * ShaderRaw.cpp
 *
 *  Created on: 10 Sep 2017
 *      Author: svenrademakers
 */
#include <fstream>

#include "ShaderLoader.hpp"

namespace sx
{
ShaderDataLoader::ShaderDataLoader(std::string fileName)
	: data(LoadFile(fileName))
	, shdrPtr(data.c_str())
{ }

const char** ShaderDataLoader::Shader()
{
	return &shdrPtr;
}

std::string ShaderDataLoader::LoadFile(const std::string& fileName) const
{
	std::string data;
	std::ifstream file(fileName);

	file.seekg(0, std::ios::end);
	data.reserve(file.tellg());
	file.seekg(0, std::ios::beg);

	data.assign((std::istreambuf_iterator<char>(file)),
			   std::istreambuf_iterator<char>());

	return data;
}
}
