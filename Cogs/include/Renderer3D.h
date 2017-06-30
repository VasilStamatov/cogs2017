#pragma once

#include "Renderer.h"

#include <unordered_map>
#include <vector>
#include <glm\mat4x4.hpp>

namespace cogs
{
		class Mesh;
		/**
		* \brief derived class from Base Renderer to handle rendering 3D meshes
		*/
		class Renderer3D : public Renderer
		{
		private:
				struct InstanceData
				{
						Mesh* mesh;
						std::vector<glm::mat4> worldmats;
				};
				std::unordered_map<VAO, InstanceData> m_entitiesMap;
		public:
				/**
				* \brief Construct the renderer and set the shader to render with
				*/
				Renderer3D();
				virtual ~Renderer3D();

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
				* \brief disposes
				*/
				void dispose() override;
		};
}