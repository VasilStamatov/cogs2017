#pragma once

#include "Component.h"

namespace cogs
{
		class Renderer2D;
		class Sprite;
		/**
		* \brief This component, given to an entity should submit it to a 2D renderer
		*/
		class SpriteRenderer : public Component
		{
		public:
				/**
				* \brief Construct the sprite renderer by giving if a reference to the sprite it will submit,
				* and the renderer the sprite will be submitted to
				*/
				SpriteRenderer(Sprite* _sprite,
						Renderer2D* _renderer);
				~SpriteRenderer();

				/**
				* Setters
				*/
				//void setSprite(Sprite& _sprite) { m_sprite = _sprite; }
				void setRenderer(Renderer2D* _renderer) { m_renderer = _renderer; }
				void setSprite(Sprite* _sprite)	  { m_sprite = _sprite; }

				Sprite* getSprite() { return m_sprite; }

		protected:
				void render() override;

				Sprite* m_sprite{ nullptr }; ///< reference to the sprite to be submitted
				Renderer2D* m_renderer{ nullptr }; ///< reference to the renderer
		};
}