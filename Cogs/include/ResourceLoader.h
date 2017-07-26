#pragma once

#include <vector>
#include <string>

namespace cogs
{
		class ResourceManager;
		class Material;

		struct SubMesh;
		struct MeshData;

		class ResourceLoader
		{
		public:
				/**
				* \brief Loads a texture using SOIL, returns true if successful.
				* \param _filePath - the filepath of the texture
				* \param _alpha			 - flag whether the texture has alpha or not
				* \param _width			 - address of an integer to write to for the texture's width
				* \param _height		 - address of an integer to write to for the texture's height
				* \param _id						 - address of an integer to write to for the texture's opengl texture ID
				*/
				static bool loadTexture(const char* _filePath, bool _alpha, int* _width, int* _height, unsigned int* _id);
				static bool loadSOIL2Texture(const std::string & _filePath, unsigned int* _id);

				/**
				* \brief Loads a texture using SOIL, returns true if successful.
				* \param _fileNames- the 6 filepaths of the cubemap (6 textures) order should be:
				*	+X (right)
				*	-X (left)
				*	+Y (top)
				*	-Y (bottom)
				*	-Z (back)
				*	+Z (front)
				* \param _alpha			 - flag whether the texture has alpha or not
				* \param _width			 - address of an integer to write to for the texture's width
				* \param _height		 - address of an integer to write to for the texture's height
				* \param _id						 - address of an integer to write to for the texture's opengl texture ID
				*/
				static bool loadCubemap(const std::vector<std::string>& _fileNames, int* _width, int* _height, unsigned int* _id);
				static bool loadSOIL2Cubemap(const std::vector<std::string>& _fileNames, unsigned int* _id);

				/**
				* \brief Loads a mesh data into the vectors using ASSIMP.
				* \param _filePath  - the filepath of the mesh to load
				* \param _subMeshes	- vector of submeshes the main mesh is made of
				* \param _positions	- vector of vec3 positions/vertices to fill
				* \param _uvs							- vector of vec2 texture coordinates to fill
				* \param _normals			- vector of vec3 normals to fill
				* \param _tangents  - vector of vec3 tangents to fill
				* \param _indices	  - vector of unsigned ints indices to fill for indexed rendering
				* \param _materials	- vector of Materials that the mesh has to fill
				*/
				static void loadMesh(ResourceManager* _rm,
						const std::string& _filePath,
						std::vector<SubMesh>& _subMeshes,
						std::vector<Material*>& _materials,
						MeshData& _meshData);
		};
}