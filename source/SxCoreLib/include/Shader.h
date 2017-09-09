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
	explicit Shader(ShaderProvider& provider);
	Shader(const Shader&) = delete;
	virtual ~Shader(){};

	void Load();

private:
	ShaderProvider& provider;
};

#endif /* SHADER_H_ */
