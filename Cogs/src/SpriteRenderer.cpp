#include "../include/SpriteRenderer.h"

#include "../include/Entity.h"
#include "../include/Sprite.h"
#include "../include/Renderer2D.h"

namespace cogs
{
		SpriteRenderer::SpriteRenderer(Sprite * _sprite, Renderer2D * _renderer)
				: m_sprite(_sprite), m_renderer(_renderer)
		{
		}
		SpriteRenderer::~SpriteRenderer()
		{
		}

		void SpriteRenderer::render()
		{
				m_renderer->submit(m_entity);
		}
}