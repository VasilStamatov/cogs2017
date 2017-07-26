#pragma once

#include "Transform.h"

namespace cogs
{
		class FPSCameraControl : public Component
		{
		public:
				FPSCameraControl(float _moveSpeed);
				~FPSCameraControl();

		protected:
				void init() override;
				void update(float _deltaTime) override;
		private:
				Transform* m_transform{ nullptr };
				float m_moveSpeed{ 1.0f }; ///< the speed/sensitivity
		};
}