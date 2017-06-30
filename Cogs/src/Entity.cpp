#include "../include/Entity.h"

namespace cogs
{
		Entity::Entity(EntityManager * _manager) : m_manager{ _manager }
		{
				m_transform = addComponent<Transform>();
		}

		Entity::Entity(EntityManager * _manager, const std::string & _name) :
				m_manager{ _manager }, m_name{ _name }
		{
				m_transform = addComponent<Transform>();
		}

		Entity::~Entity()
		{
		}

		void Entity::update(float _deltaTime)
		{
				for (auto& component : m_components)
				{
						component->update(_deltaTime);
				}
		}

		void Entity::render()
		{
				for (auto& component : m_components)
				{
						component->render();
				}
		}

		void Entity::collide(const glm::vec3& _pointA,
				const glm::vec3& _pointB,
				const glm::vec3& _normalOnB,
				Entity* _other)
		{
				for (auto& component : m_components)
				{
						component->onCollision(_pointA, _pointB, _normalOnB, _other);
				}
		}

		Transform * Entity::transform() const noexcept
		{
				return m_transform;
		}

		void Entity::setTag(const std::string & _tag)
		{
				m_tag = _tag;
		}

		const std::string & Entity::getTag() const noexcept
		{
				return m_tag;
		}

		void Entity::setName(const std::string & _name)
		{
				m_name = _name;
		}

		const std::string & Entity::getName() const noexcept
		{
				return m_name;
		}

		void Entity::setActive(bool _active)
		{
				m_isActive = _active;
				for (Transform* child : m_transform->getChildren())
				{
						child->m_entity->setActive(_active);
				}
		}

		bool Entity::isActive() const noexcept
		{
				return m_isActive;
		}

		void Entity::destroy()
		{
				m_isAlive = false;
		}

		bool Entity::isAlive() const noexcept
		{
				return m_isAlive;
		}
		void Entity::destroyOnLoad(bool _flag)
		{
				m_destroyOnLoad = _flag;
		}
		bool Entity::isDestroyedOnLoad()
		{
				return m_destroyOnLoad;
		}
}