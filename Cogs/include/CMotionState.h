#pragma once

#include <Bullet/btBulletDynamicsCommon.h>
#include <memory>

namespace cogs
{
		class Transform;

		class CMotionState final : public btMotionState
		{
		public:
				CMotionState(Transform* _transform);
			 ~CMotionState();

				virtual void getWorldTransform(btTransform & _worldTrans) const override;
				virtual void setWorldTransform(const btTransform & _worldTrans) override;
		private:
				Transform* m_transform;
		};
}