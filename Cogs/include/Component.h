#pragma once

#include "../../dependencies/include/glm/vec3.hpp"
#include "Object.h"

namespace cogs
{
		/* define a typedef for the component ID type */
		using ComponentID = unsigned int;

		/* Hide implementation details */
		namespace Internal
		{
				/* Generate a unique ID for components */
				inline ComponentID getUniqueComponentID() noexcept
				{
						/* by using a static variable every time this function is called it will refer to the same "lastID" instance
						* This way it will always return a unique ID */
						static ComponentID lastID{ 0u };
						return lastID++;
				}
		}

		/* forward declare the entity class */
		class Entity;

		/** The component class game components will inherit from*/
		class Component : public Object
		{
				friend class Entity;

		public:
				Component() {}
				//since this is going to be used polymorphically the destructor needs to have the virtual keyword
				virtual ~Component() { m_entity = nullptr; }

				Component(const Component& _other) = delete;
				Component& operator=(const Component& _rhs) = delete;

				Entity* getEntity() const noexcept { return m_entity; }

		protected:
				Entity* m_entity{ nullptr };

				virtual void init() {}
				virtual void update(float _deltaTime) {}
				virtual void render() {}
				virtual void postProcess() {}
				virtual void onCollision(const glm::vec3& _pointA,
						const glm::vec3& _pointB,
						const glm::vec3& _normalOnB,
						Entity* _other) {}
		};

		/* Get the unique ID of every component type (same component types have same IDs) */
		template<typename T>
		inline ComponentID getComponentTypeID() noexcept
		{
				/* every time this function is called with specific type "T"
				* it is instantiating this template with its own unique "typeID" variable */
				static_assert(std::is_base_of<Component, T>::value, "Must inherit from Component");

				static ComponentID typeID{ Internal::getUniqueComponentID() };
				return typeID;
		}
}