#pragma once

#include "Texture.h"

#include <string>
#include <glm\vec2.hpp>
#include <glm\vec4.hpp>

namespace cogs
{
		class GLTexture2D : public Texture
		{
		public:
				GLTexture2D(const std::string& _filePath);
			 ~GLTexture2D();

				void bind()   const override;
				void unbind() const override;

				glm::vec4 getTexCoords(int _index);
				glm::vec2 getTexOffsets(int _index);

				inline bool operator> (const GLTexture2D& _rhs) const
				{
						return m_id > _rhs.m_id;
				}
				inline bool operator!= (const GLTexture2D& _rhs) const
				{
						return m_id != _rhs.m_id;
				}

				inline const std::string& getFilePath() const { return m_filePath; }
				inline const glm::ivec2& getDims()						const { return m_tileDims; }
				inline bool isSingle()																		const { return m_isSingle; }

				inline void setDims(const glm::ivec2& _tileDims) { m_tileDims = _tileDims; }
				inline void setTextureType(bool _isSingle) { m_isSingle = _isSingle; }

		private:
				std::string m_filePath{ "" }; ///< the filepath of the texture
				glm::ivec2 m_tileDims{ 0,0 }; ///< the number of rows and cols
				bool m_isSingle{ true };
		};
}