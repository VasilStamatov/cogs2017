#include "../include/Material.h"

namespace cogs
{
		Material::Material(const std::string & _name)
		{
		}
		Material::~Material()
		{
		}

		void Material::bind()
		{
				if (!isValid())
				{
						throw "Material not valid";
				}
				int slot{ 0 };

				m_shader->use();

				if (m_diffuseMap)
				{
						m_shader->uploadValue("material." + m_diffuseMap->getName(), slot++, m_diffuseMap);
				}
				if (m_normalMap)
				{
						m_shader->uploadValue("material." + m_normalMap->getName(), slot++, m_normalMap);
				}
				if (m_specularMap)
				{
						m_shader->uploadValue("material." + m_specularMap->getName(), slot++, m_specularMap);
				}
				if (m_reflectionMap)
				{
						m_shader->uploadValue("material." + m_reflectionMap->getName(), slot++, m_reflectionMap);
				}

				m_shader->uploadValue("material.shininess", m_shininess);

				// Always good practice to set everything back to defaults once configured.
				//	glActiveTexture(GL_TEXTURE0);
				m_shader->uploadValue("", 0, (GLTexture2D*)nullptr);
		}

		void Material::unbind()
		{
				m_shader->unUse();
		}

		void Material::setShader(GLSLProgram * _shader)
		{
				m_shader = _shader;
		}
		GLSLProgram * Material::getShader()
		{
				return m_shader;
		}

		void Material::setDiffuseMap(GLTexture2D * _diffuseMap)
		{
				m_diffuseMap = _diffuseMap;
		}
		GLTexture2D * Material::getDiffuseMap()
		{
				return m_diffuseMap;
		}

		void Material::setNormalMap(GLTexture2D* _normalMap)
		{
				m_normalMap = _normalMap;
		}
		GLTexture2D* Material::getNormalMap()
		{
				return m_normalMap; 
		}

		// specular map getter and setter
		void Material::setSpecularMap(GLTexture2D* _specularMap)
		{
				m_specularMap = _specularMap; 
		}
		GLTexture2D* Material::getSpecularMap() 
		{
				return m_specularMap; 
		}

		// reflection map getter and setter
		void Material::setReflectionMap(GLTexture2D* _reflectionMap) 
		{
				m_reflectionMap = _reflectionMap;
		}
		GLTexture2D* Material::getReflectionMap()
		{
				return m_reflectionMap; 
		}

		// name getter and setter
		void Material::setName(const std::string& _name)
		{
				m_name = _name; 
		}
		const std::string& Material::getName() 
		{
				return m_name; 
		}

		// shininess getter and setter
		void Material::setShininess(float _shininess) 
		{
				m_shininess = _shininess; 
		}
		float Material::getShininess() 
		{
				return m_shininess; 
		}
		bool Material::isValid()
		{
				if (m_diffuseMap && m_shader)
				{
						return true;
				}
				return false;
		}
}