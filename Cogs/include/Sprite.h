#pragma once

#include <glm\vec2.hpp>
#include <memory>

#include "Color.h"
#include "Object.h"

namespace cogs
{
		class Material;

		class Sprite : public Object
		{
		public:
				Sprite(Material* _material, const glm::vec2& _size, const Color& _color)
						: m_size(_size), m_color(_color), m_material(_material) {}
				~Sprite() {}

				void setSize(const glm::vec2& _size) { m_size = _size; }
				void setColor(const Color& _color) { m_color = _color; }
				void setMaterial(Material* _mat) { m_material = _mat; }

				const glm::vec2& getSize() { return m_size; }
				const Color& getColor() { return m_color; }
			 Material* getMaterial() { return m_material; }
		private:
				glm::vec2 m_size{ 0.0f, 0.0f }; ///< the width and height of the sprite
				Color m_color{ Color::getWhite() }; ///< the tint of the sprite
				Material* m_material{ nullptr }; ///< the texture of the sprite
		};
}