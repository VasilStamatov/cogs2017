#pragma once

#include "Collider.h"

namespace cogs
{
		class BoxCollider final : public Collider
		{
		public:
				BoxCollider(const glm::vec3& _halfExtents)
				{
						m_collisionShape = std::make_unique<btBoxShape>(btVector3(_halfExtents.x, _halfExtents.y, _halfExtents.z));
				}
		};
}