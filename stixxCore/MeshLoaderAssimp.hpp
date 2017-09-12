/*
 * AssetLoaderAssimp.h
 *
 *  Created on: 10 Sep 2017
 *      Author: svenrademakers
 */

#ifndef MESHLOADERASSIMP_HPP_
#define MESHLOADERASSIMP_HPP_
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <MeshLoader.hpp>

class MeshLoaderAssimp
	: public sxgraphics::MeshLoader
{
public:
	MeshLoaderAssimp(const std::string& fileName);
	virtual ~MeshLoaderAssimp();

public:
	bool Next(std::vector<sxgraphics::Vertex>&, std::vector<unsigned int>&, std::vector<sxgraphics::Texture>&) override;

private:
	void processMesh(std::vector<sxgraphics::Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<sxgraphics::Texture>& textures);
    //std::vector<sxgraphics::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

private:
	Assimp::Importer importer;
	const aiScene* scene;
	uint32_t index;
};

#endif /* MESHLOADERASSIMP_HPP_ */
