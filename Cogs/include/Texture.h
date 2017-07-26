#pragma once

#include "Object.h"

namespace cogs
{
		using uint = unsigned int;

		class Texture : public Object
		{
		public:
				Texture(uint _id, int _width, int _height) : m_id(_id), m_width(_width), m_height(_height) {}
				Texture() {}
				virtual ~Texture() {}

				virtual void bind() const = 0;
				virtual void unbind() const = 0;

				inline int getWidth()	     const noexcept { return m_width; }
				inline int getHeight()     const noexcept { return m_height; }
				inline uint getTextureID() const noexcept { return m_id; }

		protected:
				uint m_id{ 0 }; ///< the ID/handle of the texture
				int m_width{ 0 }; ///< the width of the texture
				int m_height{ 0 }; ///< the height of the texture
		};
}