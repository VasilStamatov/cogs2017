#pragma once

#include <Bullet/btBulletDynamicsCommon.h>
#include <memory>

namespace cogs
{
		class Transform;
		/**
		* Implementation of bullet's motion state for this engine
		*/
		class CMotionState : public btMotionState
		{
		private:
				Transform* m_transform; ///< reference to the transform of the entity
		public:
				/**
				* Pass the address of the entity's transform,
				so the motion state can use it to set the rigidbody's position, and apply physics to it
				*/
				CMotionState(Transform* _transform);
				virtual ~CMotionState();

				/**
				* Overriden bullet functions to tie the bullet engine with this one
				*/
				virtual void getWorldTransform(btTransform & _worldTrans) const override;
				virtual void setWorldTransform(const btTransform & _worldTrans) override;
		};
}