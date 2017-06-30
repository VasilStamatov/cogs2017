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
		/**
		* \brief derived class from Base Renderer to handle rendering sprites
		*/
		class Renderer2D : public Renderer
		{
		private:
				enum BufferObjects : unsigned int
				{
						POSITION,
						COLOR,
						SIZE,
						WORLDMAT,

						INDEX,

						NUM_BUFFERS
				};

				VAO m_VAO{ 0 }; ///< the vao to be used
				VBO m_VBOs[BufferObjects::NUM_BUFFERS] = { 0 }; ///< the vbos

				struct InstancedAttributes
				{
						Material* material;
						std::vector<Color> color;
						std::vector<glm::vec2> size;
						std::vector<glm::mat4> worldMat;
				};

				//key = texture id (all sprites of the same texture to be instanced rendered)
				//value = instance data = per instance data
				std::unordered_map<unsigned int, InstancedAttributes> m_spritesMap;

		public:
				/**
				* \brief Construct the renderer and set the shader to render with
				*/
				Renderer2D();
				~Renderer2D();

				/**
				* \brief init the renderer
				*/
				void init() override;

				/**
				* Begin submission
				*/
				void begin() override;

				/**
				* \brief submit an entity to the renderer
				*/
				void submit(Entity* _entity) override;

				/**
				* End submission and sort the sprites and put them in batches
				*/
				void end() override;

				/**
				* \brief flush the renderer
				*/
				void flush() override;

				/**
				* \brief Disposes of the buffer objects
				*/
				void dispose() override;
		};
}