#pragma once

#include "Renderer.h"

#include "Color.h"
#include <glm\vec2.hpp>
#include <glm\mat4x4.hpp>
#include <unordered_map>
#include <vector>

namespace cogs
{
		class Material;

		class Renderer2D : public Renderer
		{
		public:
				Renderer2D();
				~Renderer2D();

				void init() override;
				void begin() override;
				void submit(Entity* _entity) override;
				void end() override;
				void flush() override;
				void dispose() override;

		private:
				enum class BufferObjects : unsigned char
				{
						POSITION,
						COLOR,
						SIZE,
						WORLDMAT,

						INDEX,

						NUM_BUFFERS
				};

				struct InstancedAttributes
				{
						std::vector<Color> color;
						std::vector<glm::vec2> size;
						std::vector<glm::mat4> worldMat;
						Material* material;
				};
				std::unordered_map<unsigned int, InstancedAttributes> m_spritesMap;

				VBO m_VBOs[static_cast<unsigned char>(BufferObjects::NUM_BUFFERS)] = { 0 };
				VAO m_VAO{ 0 };
		};
}