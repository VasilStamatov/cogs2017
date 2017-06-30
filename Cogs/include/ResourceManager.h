#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>

#include <glm\vec2.hpp>
#include "Color.h"

namespace cogs
{
		class GLSLProgram;
		class GLTexture2D;
		class GLCubemapTexture;
		class Material;
		class Mesh;
		class Sprite;
		class Skybox;

		/**
		* \brief Static Resource Manager class which contains a map of resources
		* of the engine as shared pointers and gives out weak pointer references when requested
		*/
		class ResourceManager
		{
		private:
				ResourceManager() {}
				~ResourceManager() {}

		private:
				static std::map<std::string, std::unique_ptr<GLSLProgram>> s_shaderMap;
				static std::map<std::string, std::unique_ptr<GLTexture2D>> s_glTex2DMap;
				static std::map<std::string, std::unique_ptr<GLCubemapTexture>> s_glTex3DMap;
				static std::map<std::string, std::unique_ptr<Material>> s_materialMap;
				static std::map<std::string, std::unique_ptr<Mesh>> s_meshMap;
				static std::map<std::string, std::unique_ptr<Sprite>> s_spriteMap;
				static std::map<std::string, std::unique_ptr<Skybox>> s_skyboxMap;

		public:
				/* GLSLProgram getters */
				static GLSLProgram* getGLSLProgram(const std::string& _name);
				static GLSLProgram* getGLSLProgram(const std::string& _name,
						const std::string& _vsFilePath,
						const std::string& _fsFilePath,
						const std::string& _gsFilePath = "");

				/* GLTexture2D getters */
				static GLTexture2D* getGLTexture2D(const std::string& _filePath);
				static GLTexture2D* getGLTexture2D(const std::string& _filePath,
						const std::string& _name);

				/* GLCubemapTexture getters */
				static GLCubemapTexture* getGLCubemap(const std::string& _name);
				static GLCubemapTexture* getGLCubemap(const std::string& _name, const std::vector<std::string>& _fileNames);

				/* Material getters */
				static Material* getMaterial(const std::string& _name);

				/* Mesh getters */
				static Mesh* getMesh(const std::string& _filePath);
				//static Mesh& getPrimitive(const std::string& _filePath);

				/* Sprite getters */
				static Sprite* getSprite(const std::string& _name);
				static Sprite* getSprite(const std::string& _name,
						Material* _material,
						const glm::vec2& _size, const Color& _color);

				static Skybox* getSkybox(const std::string& _name);
				static Skybox* getSkybox(const std::string& _name, GLSLProgram* _shader, GLCubemapTexture* m_cubemapTex, bool _isBox);

				/* clear all resource maps */
				static void clear();

				/* clear the shader map */
				static void clearGLSLPrograms();

				/* clear the GLTexture2D map */
				static void clearGLTexture2Ds();

				/* clear the GLTexture2D map */
				static void clearGLCubemaps();

				/* clear the material map */
				static void clearMaterials();

				/* clear the model map */
				static void clearModels();

				/* clear the sprite map */
				static void clearSprites();

				static void clearSkyboxed();
		};
}