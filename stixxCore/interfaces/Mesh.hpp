#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>

namespace sx
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

	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};
}
#endif
