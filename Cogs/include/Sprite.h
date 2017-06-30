#pragma once

#include <glm\vec2.hpp>
#include <memory>

#include "Color.h"

namespace cogs
{
		class Material;
		/**
				* The sprite class
				*/
		class Sprite
		{
		public:
				Sprite(const std::string& _name, Material* _material, const glm::vec2& _size, const Color& _color)
						: m_name(_name), m_size(_size), m_color(_color), m_material(_material)
				{
				}
				~Sprite() {}

				/**
				* \brief Sprite setters
				*/
				void setName(const std::string& _name) { m_name = _name; }
				void setSize(const glm::vec2& _size) { m_size = _size; }
				void setColor(const Color& _color) { m_color = _color; }
				void setMaterial(Material* _mat) { m_material = _mat; }
				/**
				* \brief Sprite getters
				*/
				const std::string& getName() { return m_name; }
				const glm::vec2& getSize() { return m_size; }
				const Color& getColor() { return m_color; }
			 Material* getMaterial() { return m_material; }
		private:
				std::string m_name{ "" }; ///< the name of the sprite
				glm::vec2 m_size{ 0.0f, 0.0f }; ///< the width and height of the sprite
				Color m_color{ Color::white }; ///< the tint of the sprite
				Material* m_material{ nullptr }; ///< the texture of the sprite
		};
}