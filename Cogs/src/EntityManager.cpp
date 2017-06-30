#include "../include/EntityManager.h"

namespace cogs
{
		EntityManager::EntityManager()
		{
		}

		EntityManager::~EntityManager()
		{
		}

		Entity * EntityManager::create()
		{
				std::unique_ptr<Entity> newEntity = std::make_unique<Entity>(this);
				m_entities.emplace_back(std::move(newEntity));
				return m_entities.back().get();
		}

		Entity * EntityManager::create(const std::string & _name)
		{
				std::unique_ptr<Entity> newEntity = std::make_unique<Entity>(this, _name);
				m_entities.emplace_back(std::move(newEntity));
				return m_entities.back().get();
		}

		void EntityManager::update(float _deltaTime)
		{
				for (auto& e : m_entities)
				{
						if (e->isActive())
						{
								e->update(_deltaTime);
						}
				}
		}

		void EntityManager::render()
		{
				for (auto& e : m_entities)
				{
						if (e->isActive())
						{
								e->render();
						}
				}
		}

		void EntityManager::refresh()
		{
				for (size_t i = 0; i < m_entities.size(); i++)
				{
						if (!m_entities.at(i)->isAlive())
						{
								m_entities.erase(m_entities.begin() + i);
								--i;
						}
				}
		}
		void EntityManager::clear()
		{
				m_entities.clear();
		}
		void EntityManager::onLevelExit()
		{
				for (size_t i = 0; i < m_entities.size(); i++)
				{
						if (m_entities.at(i)->isDestroyedOnLoad())
						{
								m_entities.erase(m_entities.begin() + i);
								--i;
						}
				}
		}
}