#ifndef MESH_H
#define MESH_H

#include "Shader.h"

namespace graphics
{
	class Mesh
	{
	public:
		virtual ~Mesh(){};
		virtual void Load() = 0;
		virtual void Draw(Shader& shader) = 0;
	};
}
#endif
