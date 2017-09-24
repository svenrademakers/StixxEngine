/*
 * ShaderGl.h
 *
 *  Created on: 9 Sep 2017
 *      Author: svenrademakers
 */

#ifndef SHADERGL_HPP_
#define SHADERGL_HPP_

#include "Shader.h"

namespace sxgraphics
{
	class ShaderGL
		 : public Shader
	{
	public:
		ShaderGL() = default;
		//ShaderGl(const ShaderGl&) = delete;
		virtual ~ShaderGL(){};

		//shader
		virtual void Load(ShaderRaw& vertex, ShaderRaw& fragment) override;
		virtual void Use() override;

	private:
		unsigned int id;
	};
}

#endif /* SHADERGL_HPP_ */
