#pragma once

#include "Collider.h"

namespace cogs
{
		/**
		* \brief Constructor to create the btSphereShape
		*/
		class SphereCollider : public Collider
		{
		public:
				/**
				* \brief Constructor to create the btSphereShape
				* \param _radius - the radius of the sphere
				*/
				SphereCollider(float _radius)
				{
						m_collisionShape = std::make_unique<btSphereShape>(_radius);
				}
				virtual ~SphereCollider() {}
		};
}