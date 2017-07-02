#pragma once

#include "Texture.h"
#include <string>
#include <vector>

namespace cogs
{
		/**
		* \brief class to handle opengl cubemap textures
		*/
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

				/**
				* \brief overriden bind/unbind functions from the base Texture class
				*/
				void bind()   const override;
				void unbind() const override;
		private:
				std::vector<std::string> m_fileNames; ///< set of the 6 filenamesof each texture
		};
}