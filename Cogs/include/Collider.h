#pragma once

#include "Component.h"

#include <Bullet\btBulletDynamicsCommon.h>
#include <memory>

namespace cogs
{
		/**
		* \brief Collider component which needs to be added before a rigidbody, as the rigidbody uses it for its contruction
		*/
		class Collider : public Component
		{
		protected:
				std::unique_ptr<btCollisionShape> m_collisionShape{ nullptr }; ///< bullet shape instance
		public:
				Collider() {}
				virtual ~Collider() {}

				/**
				* \brief scaled the collider on each axis
				*/
				void setLocalScaling(const glm::vec3& _scale)
				{
						m_collisionShape->setLocalScaling(btVector3(_scale.x, _scale.y, _scale.z));
				}

				/**
				* \brief Gets the btCollisionShape instance (usually for rigidbody construction)
				*/
				btCollisionShape* getShape() { return m_collisionShape.get(); }
		};
}