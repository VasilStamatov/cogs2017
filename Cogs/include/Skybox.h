#pragma once

#include "Object.h"

namespace cogs
{
		class GLCubemapTexture;
		class Mesh;
		class GLSLProgram;
		class ResourceManager;

		/**
		* \brief Skybox class to handle creation of a skybox and its rendering
		*/
		class Skybox : public Object
		{
		public:
				Skybox(ResourceManager* _rm, GLSLProgram* _shader, GLCubemapTexture* _cubemapTex, bool _isBox);
				~Skybox();

				/** \brief renders the skybox */
				void render();

		private:
				GLSLProgram* m_skyboxShader; ///< the skybox shader
				GLCubemapTexture* m_cubemapTex; ///< the cubemap texture
				Mesh* m_mesh; ///< the box/sphere mesh
		};
}