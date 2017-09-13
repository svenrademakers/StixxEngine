#ifndef SHADER_H_
#define SHADER_H_

#include <string>

namespace sx
{
class ShaderRaw;

class Shader
{
public:
	virtual void Load(ShaderRaw& vertex, ShaderRaw& fragment) = 0;
	virtual void Use() = 0;
	virtual ~Shader(){};
};
}
#endif /* SHADER_H_ */
