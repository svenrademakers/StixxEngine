/*
 * ShaderGl.h
 *
 *  Created on: 9 Sep 2017
 *      Author: svenrademakers
 */

#ifndef SHADERGL_H_
#define SHADERGL_H_

#include "Shader.h"
#include <boost/optional.hpp>

class ShaderGl
 	 : public Shader
{
public:
	ShaderGl() = default;
	ShaderGl(const ShaderGl&) = delete;
	virtual ~ShaderGl(){};

	//shader
	virtual void Load(ShaderProvider& provider) override;
	virtual void Use() override;

private:
	unsigned int id;
};

#endif /* SHADERGL_H_ */
