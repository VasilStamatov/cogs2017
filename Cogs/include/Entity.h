#pragma once

#include <bitset>
#include <cassert>
#include <vector>
#include <array>
#include <memory>

#include "Transform.h"

namespace cogs
{
		constexpr std::size_t MAX_COMPONENTS{ 32 };

		class EntityManager;

		class Entity
		{
				friend class EntityManager;
				friend class Physics;
		private:
				EntityManager* m_manager;
				Transform* m_transform;
				/* The Entity's tag */
				std::string m_tag{ "Default" };
				std::string m_name{ "Entity" };
				/* active flag of the entity */
				bool m_isActive{ true };
				bool m_isAlive{ true };
				bool m_destroyOnLoad{ true };
				/* An entity is also composed of numerous components
				* Therefore the components will be stored in an std::vector as shared pointers to allow polymorphism */
				std::vector<std::unique_ptr<Component>> m_components;

				/* A bitset to check the existance of a component with a specific ID */
				std::bitset<MAX_COMPONENTS> m_componentBitset;

				/* An array to get a component with specific ID */
				std::array<Component*, MAX_COMPONENTS> m_componentArray;

				/* Update this entity (all its components) */
				void update(float _deltaTime);
				/* Render this entity (all its components) */
				void render();
				/**/
				void collide(const glm::vec3& _pointA,
						const glm::vec3& _pointB,
						const glm::vec3& _normalOnB,
						Entity* _other);

		public:
				Entity(EntityManager* _manager);
				Entity(EntityManager* _manager, const std::string& _name);
				~Entity();
				
				/**
				* \brief Add components to this element of any type
				* \param[in] T is the component type
				* \param[in] TArgs is a parameter pack of types used to construct the component
				*/
				template<typename T, typename... TArgs>
				inline T* addComponent(TArgs&&... _args)
				{
						/* check if this component is not already added */
						assert(!hasComponent<T>());

						/* begin by allocating component of type T on the heap by forwarding the passed arguments to its constructor */
						std::unique_ptr<Component> component = std::make_unique<T>(std::forward<TArgs>(_args)...);
						component->m_entity = (this);
						/* Add the component to the vector (std::move is required as unique pointers cannot be copied) */
						m_components.emplace_back(std::move(component));

						/* when a component of type T is added, add it to the bitset and the array */
						m_componentArray[getComponentTypeID<T>()] = m_components.back().get();
						m_componentBitset[getComponentTypeID<T>()] = true;

						/* Call the virtual function init of the component */
						m_components.back()->init();
						return static_cast<T*>(m_components.back().get());
				}

				/**
				* \brief Checks if a specific component exists in the current entity
				*/
				template<typename T>
				inline bool hasComponent() const
				{
						/* ask the bitset if the bit if the bit at the position with the type T is true or false */
						return m_componentBitset[getComponentTypeID<T>()];
				}

				/**
				* \brief get a specific component from the m_componentArray
				* \param[out] std::weak_ptr<T> return a reference to the component requested
				*/
				template<typename T>
				inline T* getComponent() const
				{
						/* check if it has this component */
						assert(hasComponent<T>());
						//get the component pointer
						Component* component = (m_componentArray[getComponentTypeID<T>()]);
						return static_cast<T*>(component);
				}

				Transform* transform() const noexcept;

				//tag setter
				void setTag(const std::string& _tag);
				//tag getter
				const std::string& getTag() const noexcept;

				//tag setter
				void setName(const std::string& _name);
				//tag getter
				const std::string& getName() const noexcept;

				//sets the active state of the entity
				void setActive(bool _active);
				bool isActive() const noexcept;

				void destroy();
				//gets the active state of the entity
				bool isAlive() const noexcept;

				void destroyOnLoad(bool _flag);
				bool isDestroyedOnLoad();
		};
}