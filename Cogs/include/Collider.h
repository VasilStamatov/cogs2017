#pragma once

#include "Component.h"

#include <Bullet\btBulletDynamicsCommon.h>
#include <memory>

namespace cogs
{
		class Collider : public Component
		{
		public:
				Collider() {}
				virtual ~Collider() {}

				void setLocalScaling(const glm::vec3& _scale)
				{
						m_collisionShape->setLocalScaling(btVector3(_scale.x, _scale.y, _scale.z));
				}

				btCollisionShape* getShape() { return m_collisionShape.get(); }
		protected:
				std::unique_ptr<btCollisionShape> m_collisionShape{ nullptr };
		};
}