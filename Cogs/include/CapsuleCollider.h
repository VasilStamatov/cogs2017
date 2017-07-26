#pragma once

#include "Collider.h"

namespace cogs
{
		class CapsuleCollider final : public Collider
		{
		public:
				CapsuleCollider(float _radius, float _height)
				{
						m_collisionShape = std::make_unique<btCapsuleShape>(_radius, _height);
				}
		};
}