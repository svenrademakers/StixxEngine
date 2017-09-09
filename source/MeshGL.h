/*
 * MeshGL.h
 *
 *  Created on: 9 Sep 2017
 *      Author: svenrademakers
 */

#ifndef MESHGL_H_
#define MESHGL_H_

#include "Mesh.h"
#include <vector>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

class MeshGL
	: public graphics::Mesh
{
public:
	MeshGL(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
	virtual ~MeshGL();

	void Load() override;
	void Draw(graphics::Shader& shader) override;

private:
	std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    GLuint vertexArrayHandle;
    GLuint vertexBufferHandle;
    GLuint elementBufferHandle;
};

#endif /* MESHGL_H_ */
