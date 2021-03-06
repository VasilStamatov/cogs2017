#include "../include/ResourceLoader.h"

#include "../include/ResourceManager.h"
#include "../include/Mesh.h"
#include "../include/Material.h"

#include <SOIL2\SOIL2.h>
#include <GL\glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace cogs
{
		bool ResourceLoader::loadTexture(const char * _filePath, bool _alpha, int * _width, int * _height, unsigned int * _id)
		{
				unsigned char* image = SOIL_load_image(_filePath, _width, _height, 0, _alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

				if (image == nullptr)
				{
						return false;
				}

				//Generate the openGL texture object
				glGenTextures(1, _id);

				//Bind the texture object
				glBindTexture(GL_TEXTURE_2D, *_id);

				//Upload the pixels to the texture
				glTexImage2D(GL_TEXTURE_2D, 0, _alpha ? GL_RGBA : GL_RGB, *_width, *_height, 0, _alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image);
				//Generate the mipmaps
				glGenerateMipmap(GL_TEXTURE_2D);

				//Set some texture parameters
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

				//Unbind the texture
				glBindTexture(GL_TEXTURE_2D, 0);

				SOIL_free_image_data(image);

				return true;
		}

		bool ResourceLoader::loadSOIL2Texture(const std::string & _filePath, unsigned int * _id)
		{
				*_id = SOIL_load_OGL_texture(_filePath.c_str(), SOIL_LOAD_AUTO, *_id,
						SOIL_FLAG_POWER_OF_TWO
						| SOIL_FLAG_MIPMAPS
						//| SOIL_FLAG_TEXTURE_REPEATS
						| SOIL_FLAG_MULTIPLY_ALPHA
						| SOIL_FLAG_INVERT_Y);

				if (*_id == 0)
				{
						printf("SOIL loading error: '%s'\n", SOIL_last_result());
						return false;
				}
				return true;
		}

		bool ResourceLoader::loadCubemap(const std::vector<std::string>& _fileNames, int * _width, int * _height, unsigned int * _id)
		{
				//Generate the openGL handle for the cubemap
				glGenTextures(1, _id);

				//bind the cubemap
				glBindTexture(GL_TEXTURE_CUBE_MAP, *_id);

				for (GLuint i = 0; i < 6; i++)
				{
						unsigned char* image = SOIL_load_image(_fileNames.at(i).c_str(), _width, _height, 0, SOIL_LOAD_RGB);
						if (image == nullptr)
						{
								printf("SOIL loading error: '%s'\n", SOIL_last_result());
								return false;
						}
						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, *_width, *_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
						SOIL_free_image_data(image);
				}

				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				return true;
		}

		bool ResourceLoader::loadSOIL2Cubemap(const std::vector<std::string>& _fileNames, unsigned int * _id)
		{
				*_id = SOIL_load_OGL_cubemap
				(
						_fileNames.at(0).c_str(),
						_fileNames.at(1).c_str(),
						_fileNames.at(2).c_str(),
						_fileNames.at(3).c_str(),
						_fileNames.at(4).c_str(),
						_fileNames.at(5).c_str(),
						SOIL_LOAD_AUTO,
						*_id,
						SOIL_FLAG_MIPMAPS
				);

				if (*_id == 0)
				{
						printf("SOIL loading error: '%s'\n", SOIL_last_result());
						return false;
				}
				return true;
		}

		void ResourceLoader::loadMesh(ResourceManager * _rm, const std::string & _filePath, std::vector<SubMesh>& _subMeshes, std::vector<Material*>& _materials, MeshData & _meshData)
		{
				Assimp::Importer importer;

				const aiScene* scene = importer.ReadFile(_filePath,
						aiProcess_Triangulate |
						aiProcess_GenSmoothNormals |
						//aiProcess_FlipUVs |
						aiProcess_CalcTangentSpace);

				//error check
				if (!scene || !scene->mRootNode || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE)
				{
						printf("ERROR::ASSIMP:: %s \n", importer.GetErrorString());
						assert(false);
				}

				const std::string directory = _filePath.substr(0, _filePath.find_last_of('/'));

				_subMeshes.resize(scene->mNumMeshes);
				_materials.resize(scene->mNumMaterials);

				unsigned int numVertices{ 0 };
				unsigned int numIndices{ 0 };

				for (size_t i = 0; i < _subMeshes.size(); i++)
				{
						_subMeshes.at(i).m_materialIndex = scene->mMeshes[i]->mMaterialIndex;
						_subMeshes.at(i).m_numIndices = scene->mMeshes[i]->mNumFaces * 3;
						_subMeshes.at(i).m_baseVertex = numVertices;
						_subMeshes.at(i).m_baseIndex = numIndices;

						numVertices += scene->mMeshes[i]->mNumVertices;
						numIndices += _subMeshes.at(i).m_numIndices;
				}

				_meshData.m_positions.reserve(numVertices);
				_meshData.m_uvs.reserve(numVertices);
				_meshData.m_normals.reserve(numVertices);
				_meshData.m_tangents.reserve(numVertices);
				_meshData.m_indices.reserve(numIndices);

				const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);

				// Initialize the meshes in the scene one by one
				for (unsigned int i = 0; i < _subMeshes.size(); i++)
				{
						const aiMesh* paiMesh = scene->mMeshes[i];

						//load all the per-vertex data
						for (unsigned int currVert = 0; currVert < paiMesh->mNumVertices; ++currVert)
						{
								const aiVector3D pos = paiMesh->mVertices[currVert];
								const aiVector3D normal = paiMesh->mNormals[currVert];
								const aiVector3D uv = paiMesh->HasTextureCoords(0) ? paiMesh->mTextureCoords[0][currVert] : aiZeroVector;
								const aiVector3D tangent = paiMesh->mTangents[currVert];

								_meshData.m_positions.push_back(glm::vec3(pos.x, pos.y, pos.z));
								_meshData.m_uvs.push_back(glm::vec2(uv.x, uv.y));
								_meshData.m_normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
								_meshData.m_tangents.push_back(glm::vec3(tangent.x, tangent.y, tangent.z));
						}

						//load all the indices for indexed rendering
						for (unsigned int currFace = 0; currFace < paiMesh->mNumFaces; ++currFace)
						{
								const aiFace& face = paiMesh->mFaces[currFace];
								assert(face.mNumIndices == 3);
								_meshData.m_indices.push_back(face.mIndices[0]);
								_meshData.m_indices.push_back(face.mIndices[1]);
								_meshData.m_indices.push_back(face.mIndices[2]);
						}
				}

				for (size_t i = 0; i < scene->mNumMaterials; i++)
				{
						aiMaterial* paiMaterial = scene->mMaterials[i];

						std::string materialName = directory + "/" + scene->mRootNode->mName.C_Str() + std::to_string(i);

						Material* material = _rm->get<Material>(materialName);

						if (!material->isValid())
						{
								//load materials data
								if (paiMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
								{
										aiString str;
										paiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &str);
										std::string filepath = directory + "/" + str.C_Str();
										material->setDiffuseMap(_rm->get<GLTexture2D>(filepath, filepath));
								}
								if (paiMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0)
								{
										aiString str;
										paiMaterial->GetTexture(aiTextureType_SPECULAR, 0, &str);
										std::string filepath = directory + "/" + str.C_Str();
										material->setSpecularMap(_rm->get<GLTexture2D>(filepath, filepath));
								}
								if (paiMaterial->GetTextureCount(aiTextureType_AMBIENT) > 0)
								{
										aiString str;
										paiMaterial->GetTexture(aiTextureType_AMBIENT, 0, &str);
										std::string filepath = directory + "/" + str.C_Str();
										material->setReflectionMap(_rm->get<GLTexture2D>(filepath, filepath));
								}
								if (paiMaterial->GetTextureCount(aiTextureType_HEIGHT) > 0)
								{
										aiString str;
										paiMaterial->GetTexture(aiTextureType_HEIGHT, 0, &str);
										std::string filepath = directory + "/" + str.C_Str();
										material->setNormalMap(_rm->get<GLTexture2D>(filepath, filepath));
								}
								material->setShader(_rm->get<GLSLProgram>("Default3D", "Shaders/Default3DUnlit.vs", "Shaders/Default3DUnlit.fs"));
						}
						_materials.at(i) = material;
				}
		}
}