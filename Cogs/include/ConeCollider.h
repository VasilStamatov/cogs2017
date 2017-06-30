#pragma once

#include "Collider.h"

namespace cogs
{
		/**
		* \brief Instantiates a btConeShape using the passed radius and height
		*/
		class ConeCollider : public Collider
		{
		public:
				/**
				* \brief create the btConeShape
				* \param _radius - the radius of the capsule
				* \param _height - the height of the capsule
				*/
				ConeCollider(float _radius, float _height)
				{
						m_collisionShape = std::make_unique<btConeShape>(_radius, _height);
				}
				virtual ~ConeCollider() {}

		private:

		};
}