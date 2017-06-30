#pragma once

#include <memory>

#include "Texture.h"

namespace cogs
{
		/**
		* \brief Framebuffer class for handling rendertargets
		*/
		class Framebuffer : public Texture
		{
		public:
				Framebuffer() {}
				~Framebuffer();

				/**
				* \brief overriden bind/unbind functions from the base Texture class
				*/
				void bind()   const override;
				void unbind() const override;

				/**
				* \brief getters for the fbo/rbo IDs
				*/
				uint getFBO()	const noexcept { return m_fboID; }
				uint getRBO()	const noexcept { return m_rboID; }

				/**
				* \brief creates a new Framebuffer instance and returns a shared ptr of it using move semantics
				* \param[in] _width - the width of the framebuffer
				* \param[in] _height - the height of the framebuffer
				*/
				static std::unique_ptr<Framebuffer> create(unsigned int _width, unsigned int _height);

				/**
				* \brief gets the current active framebuffer
				*/
				static Framebuffer* getCurrentActive() { return s_currentActive; }

				/**
				* \brief sets the current active framebuffer
				*/
				static void setActive(Framebuffer* _fb);

		private:
				static Framebuffer* s_currentActive; ///< the current active framebuffer

				uint m_fboID{ 0 }; ///< this framebuffer's fbo id
				uint m_rboID{ 0 }; ///< this framebuffer's rbo id
		};
}