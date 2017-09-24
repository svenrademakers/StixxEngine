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

class MeshGL
	: public Mesh
{
public:
	MeshGL();
	MeshGL(const MeshGL&) = delete;

	virtual ~MeshGL();

	void Load() override;
	void Draw(Shader& shader) override;

    void Vertices(const std::vector<sxgraphics::Vertex>& vertices) override;
    void Indices(const std::vector<unsigned int>& indices) override;
    void Textures(const std::vector<sxgraphics::Texture>& textures) override;

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
