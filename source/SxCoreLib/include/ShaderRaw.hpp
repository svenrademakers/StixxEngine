/*
 * ShaderFile.hpp
 *
 *  Created on: 10 Sep 2017
 *      Author: svenrademakers
 */

#ifndef SHADERFILE_HPP_
#define SHADERFILE_HPP_

#include <string>

namespace graphics
{

class ShaderRaw
{
public:
	virtual ~ShaderRaw(){};
	virtual const char** Shader()  = 0;
};

class ShaderDataLoader
	: public ShaderRaw
{
public:
	ShaderDataLoader(std::string fileName);
	virtual ~ShaderDataLoader() = default;

	const char** Shader() override;

private:
	std::string LoadFile(const std::string& fileName) const;

	const std::string data;
	const char * shdrPtr;
};
}

#endif /* SXCORELIB_INCLUDE_SHADERFILE_HPP_ */
