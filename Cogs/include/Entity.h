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

		class Entity : public Object
		{
				friend class EntityManager;
				friend class Physics;

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
						T* newComponent(new T(std::forward<TArgs>(_args)...));
						newComponent->m_entity = this;
						std::unique_ptr<Component> uPtr{ newComponent };
						/* Add the component to the vector (std::move is required as unique pointers cannot be copied) */
						m_components.emplace_back(std::move(uPtr));

						/* when a component of type T is added, add it to the bitset and the array */
						m_componentArray[getComponentTypeID<T>()] = newComponent;
						m_componentBitset[getComponentTypeID<T>()] = true;

						/* Call the virtual function init of the component */
						m_components.back()->init();
						return newComponent;
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

				template<typename T>
				inline T* getComponent() const
				{
						assert(hasComponent<T>());
						auto ptr(m_componentArray[getComponentTypeID<T>()]);
						return static_cast<T*>(ptr);
				}

				Transform* transform() const noexcept;

				//tag setter
				void setTag(const std::string& _tag);
				//tag getter
				const std::string& getTag() const noexcept;

				//sets the active state of the entity
				void setActive(bool _active);
				bool isActive() const noexcept;

				void destroyOnLoad(bool _flag);
				bool isDestroyedOnLoad();

		private:
				/* Update this entity (all its components) */
				void update(float _deltaTime);
				/* Render this entity (all its components) */
				void render();
				/**/
				void collide(const glm::vec3& _pointA,
						const glm::vec3& _pointB,
						const glm::vec3& _normalOnB,
						Entity* _other);

		private:
				EntityManager* m_manager;
				Transform* m_transform;
				/* The Entity's tag */
				std::string m_tag{ "Default" };
				/* active flag of the entity */
				bool m_isActive{ true };
				bool m_destroyOnLoad{ true };
				/* An entity is also composed of numerous components
				* Therefore the components will be stored in an std::vector as shared pointers to allow polymorphism */
				std::vector<std::unique_ptr<Component>> m_components;

				/* A bitset to check the existance of a component with a specific ID */
				std::bitset<MAX_COMPONENTS> m_componentBitset;

				/* An array to get a component with specific ID */
				std::array<Component*, MAX_COMPONENTS> m_componentArray;
		};
}