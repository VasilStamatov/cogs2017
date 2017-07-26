#pragma once

#include "Entity.h"

namespace cogs
{
		class EntityManager
		{
		private:
				std::vector<std::unique_ptr<Entity>> m_entities;

		public:
				EntityManager();
				~EntityManager();

				EntityManager(const EntityManager& _other) = delete;
				EntityManager& operator=(const EntityManager& _rhs) = delete;

				Entity* create();
				Entity* create(const std::string& _name);

				void update(float _deltaTime);
				void render();
				void refresh();
				void clear();
				void onLevelExit();
		};
}