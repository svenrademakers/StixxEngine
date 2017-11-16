#ifndef MESHLOADERASSIMP_HPP_
#define MESHLOADERASSIMP_HPP_

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "interfaces/MeshLoader.hpp" 

class MeshLoaderAssimp
	: public sx::MeshLoader
{
public:
	MeshLoaderAssimp(const std::string& fileName);
	virtual ~MeshLoaderAssimp();

public:
	bool Next(sx::Mesh& mesh) override;

private:
	void processMesh(std::vector<sx::Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<sx::Texture>& textures);
    //std::vector<sxgraphics::Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

private:
	Assimp::Importer importer;
	const aiScene* scene;
	uint32_t index;
};

#endif /* MESHLOADERASSIMP_HPP_ */
