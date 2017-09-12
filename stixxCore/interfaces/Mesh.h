#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include "Shader.h"

namespace sxgraphics
{
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
	};

	struct Texture
	{
		unsigned int id;
		std::string type;
	    std::string path;
	};

	class Mesh
	{
	public:
		virtual ~Mesh(){};
		virtual void Load() = 0;
		virtual void Draw(Shader& shader) = 0;

	    virtual void Vertices(const std::vector<sxgraphics::Vertex>& vertices) = 0;
	    virtual void Indices(const std::vector<unsigned int>& indices) = 0;
	    virtual void Textures(const std::vector<sxgraphics::Texture>& textures) = 0;
	};
}
#endif
