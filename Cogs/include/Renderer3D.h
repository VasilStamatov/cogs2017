#pragma once

#include "Renderer.h"

#include <unordered_map>
#include <vector>
#include <glm\mat4x4.hpp>

namespace cogs
{
		class Mesh;

		class Renderer3D : public Renderer
		{
		public:
				Renderer3D();
				virtual ~Renderer3D();

			 void init() override;
				void begin() override;
				void submit(Entity* _entity) override;
				void end() override;
				void flush() override;
				void dispose() override;

		private:
				struct InstanceData
				{
						std::vector<glm::mat4> worldmats;
						Mesh* mesh;
				};

		private:
				std::unordered_map<VAO, InstanceData> m_entitiesMap;
		};
}