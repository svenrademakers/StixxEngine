#include "AssetImporterAssimp.hpp"
#include <iostream>
#include <vector>

AssetImporterAssimp::~AssetImporterAssimp()
{}

void AssetImporterAssimp::Load(const char * fileName)
{
	scene = importer.ReadFile(fileName,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!scene)
		std::cerr << importer.GetErrorString();
}

bool AssetImporterAssimp::Next(sx::Mesh& mesh)
{
	if (index == scene->mNumMeshes)
	return false;

	std::vector<sx::Texture> textures;
    processMesh(mesh.vertices, mesh.indices, textures);
    return true;
}

void AssetImporterAssimp::processMesh(std::vector<sx::Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<sx::Texture>& textures)
{
    aiMesh* mesh = scene->mMeshes[index];

    // Walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
    	sx::Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
	// texture coordinates
	if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
	{
		glm::vec2 vec;
		// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
		// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
		vec.x = mesh->mTextureCoords[0][i].x;
		vec.y = mesh->mTextureCoords[0][i].y;
		vertex.TexCoords = vec;
	}
	else
		vertex.TexCoords = glm::vec2(0.0f, 0.0f);

	vertices.push_back(vertex);
    }
//        // tangent
//        vector.x = mesh->mTangents[i].x;
//        vector.y = mesh->mTangents[i].y;
//        vector.z = mesh->mTangents[i].z;
//        vertex.Tangent = vector;
//        // bitangent
//        vector.x = mesh->mBitangents[i].x;
//        vector.y = mesh->mBitangents[i].y;
//        vector.z = mesh->mBitangents[i].z;
//        vertex.Bitangent = vector;
//        vertices.push_back(vertex);
//    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
//    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

//    // 1. diffuse maps
//    std::vector<sxgraphics::Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//    // 2. specular maps
//    std::vector<sxgraphics::Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//    // 3. normal maps
//    std::vector<sxgraphics::Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
//    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
//    // 4. height maps
//    std::vector<sxgraphics::Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
//    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
}

//std::vector<sxgraphics::Texture> AssetLoaderAssimp::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
//{
//    std::vector<sxgraphics::Texture> textures;
//    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
//    {
//        aiString str;
//        mat->GetTexture(type, i, &str);
//        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
//        bool skip = false;
//        for(unsigned int j = 0; j < textures_loaded.size(); j++)
//        {
//            if(textures_loaded[j].path.compare(str) == 0)
//            {
//                textures.push_back(textures_loaded[j]);
//                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
//                break;
//            }
//        }
//        if(!skip)
//        {   // if texture hasn't been loaded already, load it
//            sxgraphics::Texture texture;
//            //texture.id = TextureFromFile(str.C_Str(), this->directory);
//            texture.type = typeName;
//            texture.path = str;
//            textures.push_back(texture);
//            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
//        }
//    }
//    return textures;
//}
