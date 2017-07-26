#pragma once

#include "Component.h"

namespace cogs
{
		class Renderer2D;
		class Sprite;
		
		class SpriteRenderer : public Component
		{
		public:
				SpriteRenderer(Sprite* _sprite, Renderer2D* _renderer);
				~SpriteRenderer();

				void setRenderer(Renderer2D* _renderer) { m_renderer = _renderer; }
				void setSprite(Sprite* _sprite)	  { m_sprite = _sprite; }

				Sprite* getSprite() const noexcept { return m_sprite; }

		protected:
				void render() override;

		private:
				Sprite* m_sprite{ nullptr }; ///< reference to the sprite to be submitted
				Renderer2D* m_renderer{ nullptr }; ///< reference to the renderer
		};
}