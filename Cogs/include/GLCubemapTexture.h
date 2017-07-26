#pragma once

#include "Texture.h"
#include <string>
#include <vector>

namespace cogs
{
		class GLCubemapTexture : public Texture
		{
		public:
				// Loads a cubemap texture from 6 individual texture faces
				// Order should be:
				// +X (right)
				// -X (left)
				// +Y (top)
				// -Y (bottom)
				// -Z (back)
				// +Z (front)
				GLCubemapTexture(const std::vector<std::string>& _fileNames);
			 ~GLCubemapTexture();

				void bind()   const override;
				void unbind() const override;
		private:
				std::vector<std::string> m_fileNames;
		};
}