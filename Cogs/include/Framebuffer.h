#pragma once

#include <memory>

#include "Texture.h"

namespace cogs
{
		class Framebuffer : public Texture
		{
		public:
				Framebuffer() {}
				~Framebuffer();

				void bind()   const override;
				void unbind() const override;

				uint getFBO()	const noexcept { return m_fboID; }
				uint getRBO()	const noexcept { return m_rboID; }

				static std::unique_ptr<Framebuffer> create(unsigned int _width, unsigned int _height);

				static Framebuffer* getCurrentActive() { return s_currentActive; }
				static void setActive(Framebuffer* _fb);

		private:
				static Framebuffer* s_currentActive; 

				uint m_fboID{ 0 };
				uint m_rboID{ 0 };
		};
}