#pragma once

#include <memory>
#include <string>

#include "GLSLProgram.h"
#include "GLTexture2D.h"

namespace cogs
{
		class Material : public Object
		{
		public:
				Material();
				~Material();

				void bind();
				void unbind();

				void setShader(GLSLProgram* _shader);
				GLSLProgram* getShader();

				void setDiffuseMap(GLTexture2D* _diffuseMap);
				GLTexture2D* getDiffuseMap();

				void setNormalMap(GLTexture2D* _normalMap);
				GLTexture2D* getNormalMap();

				void setSpecularMap(GLTexture2D* _specularMap);
				GLTexture2D* getSpecularMap();

				void setReflectionMap(GLTexture2D* _reflectionMap);
				GLTexture2D* getReflectionMap();

				void setShininess(float _shininess);
				float getShininess();

				bool isValid();

		private:
				float m_shininess{ 8.0f }; ///< shininess value of the material

				GLSLProgram* m_shader{ nullptr };

				GLTexture2D* m_diffuseMap{ nullptr }; ///< the diffuse map texture
				GLTexture2D* m_normalMap{ nullptr }; ///< the normal map texture
				GLTexture2D* m_specularMap{ nullptr }; ///< the specular map texture
				GLTexture2D* m_reflectionMap{ nullptr }; ///< the reflection map texture

		};
}