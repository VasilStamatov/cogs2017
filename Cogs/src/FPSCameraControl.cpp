#include "../include/FPSCameraControl.h"

#include "../include/Entity.h"
#include "../include/Input.h"

namespace cogs
{
		FPSCameraControl::FPSCameraControl(float _moveSpeed) : m_moveSpeed(_moveSpeed)
		{
		}
		FPSCameraControl::~FPSCameraControl()
		{
		}
		void FPSCameraControl::init()
		{
				m_transform = m_entity->transform();
		}
		void FPSCameraControl::update(float _deltaTime)
		{
				// Handle movement

				// Forward
				if (Input::isKeyDown(KeyCode::W))
				{
						m_transform->translate(m_transform->localForwardAxis() * m_moveSpeed * _deltaTime);
				}

				// Backwards
				if (Input::isKeyDown(KeyCode::S))
				{
						m_transform->translate(m_transform->localForwardAxis() * -m_moveSpeed * _deltaTime);
				}

				// Left
				if (Input::isKeyDown(KeyCode::A))
				{
						m_transform->translate(m_transform->localRightAxis() * -m_moveSpeed * _deltaTime);
				}

				// Right
				if (Input::isKeyDown(KeyCode::D))
				{
						m_transform->translate(m_transform->localRightAxis() * m_moveSpeed * _deltaTime);
				}

				const glm::vec2& mouseMotion = Input::getMouseMotion();

				// Handle rotation
				if (mouseMotion.x != 0.0f || mouseMotion.y != 0.0f)
				{
						//how much the mouse moves horizontally
						float xAxisRotation = (-mouseMotion.y * m_moveSpeed * _deltaTime);
						//how much the mouse moves vertically
						float yAxisRotation = (-mouseMotion.x * m_moveSpeed * _deltaTime);

						//rotate around the x axis locally and around the y axis using the world up vector
						//this locks rotating around z axis, but instroduces gimbal locking again
						m_transform->rotate(m_transform->localRightAxis(), glm::radians(xAxisRotation));
						m_transform->rotate(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(yAxisRotation));

						/*const glm::vec3& orientation = m_transform->localOrientation();

						printf("Orientation x: %f\n", orientation.x);
						printf("Orientation x degree: %f\n\n", glm::degrees(orientation.x));

						printf("Orientation y: %f\n", orientation.y);
						printf("Orientation y degree: %f\n\n", glm::degrees(orientation.y));

						printf("Orientation z: %f\n", orientation.z);
						printf("Orientation z degree: %f\n\n", glm::degrees(orientation.z));*/

						Input::setMouseMotion(0.0f, 0.0f);
				}
		}
}
