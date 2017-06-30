#include "../include/ResourceManager.h"
#include "../include/Utils.h"
#include "../include/GLSLProgram.h"
#include "../include/GLTexture2D.h"
#include "../include/GLCubemapTexture.h"
#include "../include/Material.h"
#include "../include/Mesh.h"
#include "../include/Sprite.h"
#include "../include/Skybox.h"

namespace cogs
{
		std::map<std::string, std::unique_ptr<GLSLProgram>> ResourceManager::s_shaderMap = {};
		std::map<std::string, std::unique_ptr<GLTexture2D>> ResourceManager::s_glTex2DMap = {};
		std::map<std::string, std::unique_ptr<Material>> ResourceManager::s_materialMap = {};
		std::map<std::string, std::unique_ptr<Mesh>> ResourceManager::s_meshMap = {};
		std::map<std::string, std::unique_ptr<Sprite>> ResourceManager::s_spriteMap = {};
		std::map<std::string, std::unique_ptr<GLCubemapTexture>> ResourceManager::s_glTex3DMap = {};
		std::map<std::string, std::unique_ptr<Skybox>> ResourceManager::s_skyboxMap = {};

		GLSLProgram* ResourceManager::getGLSLProgram(const std::string & _name)
		{
				auto iter = s_shaderMap.find(_name);

				//check if it's not in the map
				if (iter == s_shaderMap.end())
				{
						//return an empty/expired pointer
						return nullptr;
				}
				else
				{
						//return the found resource
						return iter->second.get();
				}
		}

		GLSLProgram* ResourceManager::getGLSLProgram(const std::string & _name,
				const std::string & _vsFilePath, const std::string & _fsFilePath, const std::string & _gsFilePath)
		{
				auto iter = s_shaderMap.find(_name);

				//check if it's not in the map
				if (iter == s_shaderMap.end())
				{
						//if the resource does not exist, create it
						std::unique_ptr<GLSLProgram> newShader =
								std::make_unique<GLSLProgram>(_name, _vsFilePath, _fsFilePath, _gsFilePath);

						//insert it into the resource map
						s_shaderMap.insert(std::make_pair(_name, std::move(newShader)));

						//return it as it 100% exists
						return s_shaderMap.at(_name).get();
				}
				else
				{
						//return the found resource
						return iter->second.get();
				}
		}

		GLTexture2D* ResourceManager::getGLTexture2D(const std::string & _filePath)
		{
				auto iter = s_glTex2DMap.find(_filePath);

				//check if it's not in the map
				if (iter == s_glTex2DMap.end())
				{
						// if the resource does not exist, create it
						std::unique_ptr<GLTexture2D> newTexture =
								std::make_unique<GLTexture2D>(_filePath, _filePath);

						//insert it into the resource map
						s_glTex2DMap.insert(std::make_pair(_filePath, std::move(newTexture)));

						//return it as it 100% exists
						return s_glTex2DMap.at(_filePath).get();
				}
				else
				{
						//return the found resource
						return iter->second.get();
				}
		}

		GLTexture2D* ResourceManager::getGLTexture2D(const std::string & _filePath,
				const std::string & _name)
		{
				auto iter = s_glTex2DMap.find(_filePath);

				//check if it's not in the map
				if (iter == s_glTex2DMap.end())
				{
						// if the resource does not exist, create it
						std::unique_ptr<GLTexture2D> newTexture =
								std::make_unique<GLTexture2D>(_name, _filePath);

						//insert it into the resource map
						s_glTex2DMap.insert(std::make_pair(_filePath, std::move(newTexture)));

						//return it as it 100% exists
						return s_glTex2DMap.at(_filePath).get();
				}
				else
				{
						//return the found resource
						return iter->second.get();
				}
		}

		GLCubemapTexture* ResourceManager::getGLCubemap(const std::string & _name)
		{
				auto iter = s_glTex3DMap.find(_name);

				//check if it's not in the map
				if (iter == s_glTex3DMap.end())
				{
						return nullptr;
				}
				else
				{
						//return the found resource
						return iter->second.get();
				}
		}

		GLCubemapTexture* ResourceManager::getGLCubemap(const std::string & _name, const std::vector<std::string>& _fileNames)
		{
				auto iter = s_glTex3DMap.find(_name);

				//check if it's not in the map
				if (iter == s_glTex3DMap.end())
				{
						// if the resource does not exist, create it
						std::unique_ptr<GLCubemapTexture> newTexture =
								std::make_unique<GLCubemapTexture>(_name, _fileNames);

						//insert it into the resource map
						s_glTex3DMap.insert(std::make_pair(_name, std::move(newTexture)));

						//return it as it 100% exists
						return s_glTex3DMap.at(_name).get();
				}
				else
				{
						//return the found resource
						return iter->second.get();
				}
		}

		Material* ResourceManager::getMaterial(const std::string & _name)
		{
				auto iter = s_materialMap.find(_name);

				//check if it's not in the map
				if (iter == s_materialMap.end())
				{
						// if the resource does not exist, create it
						std::unique_ptr<Material> newMaterial = std::make_unique<Material>(_name);

						//insert it into the resource map
						s_materialMap.insert(std::make_pair(_name, std::move(newMaterial)));

						//return it as it 100% exists
						return s_materialMap.at(_name).get();
				}
				else
				{
						//return the found resource
						return iter->second.get();
				}
		}

		Mesh* ResourceManager::getMesh(const std::string & _filePath)
		{
				auto iter = s_meshMap.find(_filePath);

				//check if it's not in the map
				if (iter == s_meshMap.end())
				{
						// if the resource does not exist, create it
						std::unique_ptr<Mesh> newMesh = std::make_unique<Mesh>(_filePath);

						//insert it into the resource map
						s_meshMap.insert(std::make_pair(_filePath, std::move(newMesh)));

						//return it as it 100% exists
						return s_meshMap.at(_filePath).get();
				}
				else
				{
						//return the found resource
						return iter->second.get();
				}
		}

		Sprite* ResourceManager::getSprite(const std::string & _name)
		{
				auto iter = s_spriteMap.find(_name);

				//check if it's not in the map
				if (iter == s_spriteMap.end())
				{
						//return an empty/expired pointer
						return nullptr;
				}
				else
				{
						//return the found resource
						return iter->second.get();
				}
		}

		Sprite* ResourceManager::getSprite(const std::string& _name,
				Material* _material,
				const glm::vec2& _size, const Color& _color)
		{
				auto iter = s_spriteMap.find(_name);

				//check if it's not in the map
				if (iter == s_spriteMap.end())
				{
						// if the resource does not exist, create it
						std::unique_ptr<Sprite> newMaterial =
								std::make_unique<Sprite>(_name, _material, _size, _color);

						//insert it into the resource map
						s_spriteMap.insert(std::make_pair(_name, std::move(newMaterial)));

						//return it as it 100% exists
						return s_spriteMap.at(_name).get();
				}
				else
				{
						//return the found resource
						return iter->second.get();
				}
		}

		Skybox * ResourceManager::getSkybox(const std::string & _name)
		{
				auto iter = s_skyboxMap.find(_name);

				//check if it's not in the map
				if (iter == s_skyboxMap.end())
				{
						//return an empty/expired pointer
						return nullptr;
				}
				else
				{
						//return the found resource
						return iter->second.get();
				}
		}

		Skybox * ResourceManager::getSkybox(const std::string & _name, GLSLProgram * _shader, GLCubemapTexture * m_cubemapTex, bool _isBox)
		{
				auto iter = s_skyboxMap.find(_name);

				//check if it's not in the map
				if (iter == s_skyboxMap.end())
				{
						//if the resource does not exist, create it
						std::unique_ptr<Skybox> newShader =
								std::make_unique<Skybox>(_shader, m_cubemapTex, _isBox);

						//insert it into the resource map
						s_skyboxMap.insert(std::make_pair(_name, std::move(newShader)));

						//return it as it 100% exists
						return s_skyboxMap.at(_name).get();
				}
				else
				{
						//return the found resource
						return iter->second.get();
				}
		}

		void ResourceManager::clear()
		{
				clearGLSLPrograms();
				clearGLTexture2Ds();
				clearGLCubemaps();
				clearMaterials();
				clearModels();
				clearSprites();
				clearSkyboxed();
		}

		void ResourceManager::clearGLSLPrograms()
		{
				s_shaderMap.clear();
		}

		void ResourceManager::clearGLTexture2Ds()
		{
				s_glTex2DMap.clear();
		}

		void ResourceManager::clearGLCubemaps()
		{
				s_glTex3DMap.clear();
		}

		void ResourceManager::clearMaterials()
		{
				s_materialMap.clear();
		}

		void ResourceManager::clearModels()
		{
				s_meshMap.clear();
		}

		void ResourceManager::clearSprites()
		{
				s_spriteMap.clear();
		}
		void ResourceManager::clearSkyboxed()
		{
				s_skyboxMap.clear();
		}
}