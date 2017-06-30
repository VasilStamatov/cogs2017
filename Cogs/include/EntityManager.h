#pragma once

#include "Entity.h"

namespace cogs
{
		class EntityManager
		{
		private:
				// Atoms and marks storage.
				std::vector<std::unique_ptr<Entity>> m_entities;

		public:
				EntityManager();
				~EntityManager();

				Entity* create();
				Entity* create(const std::string& _name);

				void update(float _deltaTime);
				void render();
				void refresh();
				void clear();
				void onLevelExit();
		};
}