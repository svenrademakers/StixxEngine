#ifndef SHADER_H_
#define SHADER_H_

class ShaderProvider
{
public:
	virtual ~ShaderProvider(){};
	virtual const char* VertexShader() const = 0;
	virtual const char* FragmentShader() const = 0;
};

class Shader
{
public:
	virtual void Load(ShaderProvider& provider) = 0;
	virtual ~Shader(){};
};

#endif /* SHADER_H_ */
