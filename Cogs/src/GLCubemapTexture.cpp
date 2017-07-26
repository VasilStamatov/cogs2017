#include "../include/GLCubemapTexture.h"
#include "../include/ResourceLoader.h"

#include <GL\glew.h>

namespace cogs
{
		GLCubemapTexture::GLCubemapTexture(const std::vector<std::string>& _fileNames)
		{
				m_fileNames = _fileNames;

				if (!ResourceLoader::loadSOIL2Cubemap(m_fileNames, &m_id))
				{
						throw std::runtime_error("Texture failed to load");
				}
		}

		GLCubemapTexture::~GLCubemapTexture()
		{
				if (m_id != 0)
				{
						glDeleteTextures(1, &m_id);
						m_id = 0;
				}
		}
		void GLCubemapTexture::bind() const
		{
				glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
		}
		void GLCubemapTexture::unbind() const
		{
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
}