/*
 * MeshGL.cpp
 *
 *  Created on: 9 Sep 2017
 *      Author: svenrademakers
 */

#include <MeshGL.h>

namespace sxgraphics
{
MeshGL::MeshGL(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures)
	: vertices(vertices)
	, indices(indices)
	, textures(textures)
	, vertexArrayHandle(0)
	, vertexBufferHandle(0)
	, elementBufferHandle(0)
 {
	Load();
 }

MeshGL::~MeshGL()
{}

void MeshGL::Load()
{
    glGenVertexArrays(1, &vertexArrayHandle);
    glGenBuffers(1, &vertexBufferHandle);
    glGenBuffers(1, &elementBufferHandle);

    glBindVertexArray(vertexArrayHandle);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
}

void MeshGL::Draw(Shader& shader)
{
    // draw mesh
    glBindVertexArray(vertexArrayHandle);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
}
