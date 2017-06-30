#pragma once

#include "Transform.h"

namespace cogs
{
		/**
		* A component used to give the camera a fps-styled controls (wasd movement and rotation with the mouse)
		*/
		class FPSCameraControl : public Component
		{
		public:
				FPSCameraControl(float _moveSpeed);
				~FPSCameraControl();

				/**
				* The initialize component function
				*/
				void init() override;

				/**
				* The update component function
				*/
				void update(float _deltaTime) override;

		private:
				Transform* m_transform{ nullptr };
				float m_moveSpeed{ 1.0f }; ///< the speed/sensitivity
		};
}