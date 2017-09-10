/*
 * MeshGL.h
 *
 *  Created on: 9 Sep 2017
 *      Author: svenrademakers
 */

#ifndef MESHGL_HPP_
#define MESHGL_HPP_

#include "Mesh.h"
#include <vector>
#include <string>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sxgraphics
{
struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Texture
{
	GLuint id;
	std::string type;
};

class MeshGL
	: public Mesh
{
public:
	MeshGL(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices,
			const std::vector<Texture>& textures);
	virtual ~MeshGL();

	void Load() override;
	void Draw(Shader& shader) override;

private:
	std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    GLuint vertexArrayHandle;
    GLuint vertexBufferHandle;
    GLuint elementBufferHandle;
};
}

#endif /* MESHGL_HPP_ */
