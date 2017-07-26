#include "../include/Camera.h"

#include "../include/Entity.h"
#include "../include/Window.h"

#include "../include/Skybox.h"
#include "../include/Framebuffer.h"
#include "../include/BulletDebugRenderer.h"

#include <glm\gtc\matrix_transform.hpp>

namespace cogs
{
		Camera* Camera::s_mainCamera;
		Camera* Camera::s_currentCamera;
		std::vector<Camera*> Camera::s_allCameras;

		Camera::Camera() {}

		Camera::~Camera()
		{
				resetProjectionMatrix();

				if (s_mainCamera == this)
				{
						s_mainCamera = nullptr;
				}

				for (size_t i = 0; i < s_allCameras.size(); i++)
				{
						if (s_allCameras.at(i) == this)
						{
								s_allCameras.erase(s_allCameras.begin() + i);

								i--;
						}
				}

				m_transform = nullptr;
		}

		void Camera::init()
		{
				m_transform = m_entity->transform();
				refreshInternalTransform();

				m_frustum.setCamInternals(glm::radians((float)m_fov), Window::getAspect(), m_nearPlane, m_farPlane);
				updateView();

				if (s_mainCamera == nullptr && m_entity->getName() == "MainCamera")
				{
						setMain(this);
				}
				addCamera(this);
		}

		void Camera::update(float _deltaTime)
		{
				if (!(*m_transform == m_oldTransform))
				{
						updateView();
				}
		}

		void Camera::setFoV(int _value)
		{
				if (m_fov < 1)
				{
						m_fov = 1;
				}
				else if (m_fov > 179)
				{
						m_fov = 179;
				}
				m_frustum.setCamInternals(glm::radians((float)m_fov), Window::getAspect(), m_nearPlane, m_farPlane);
		}

		void Camera::offsetFoV(int _value)
		{
				m_fov += _value;
				if (m_fov < 1)
				{
						m_fov = 1;
				}
				else if (m_fov > 179)
				{
						m_fov = 179;
				}
				m_frustum.setCamInternals(glm::radians((float)m_fov), Window::getAspect(), m_nearPlane, m_farPlane);
		}

		void Camera::setSize(float _value)
		{
				m_size = _value;
				if (m_size < 1.0f)
				{
						m_size = 1.0f;
				}
		}

		void Camera::offsetSize(float _value)
		{
				m_size += _value;
				if (m_size < 1.0f)
				{
						m_size = 1.0f;
				}
		}

		void Camera::setNearPlane(float _value)
		{
				m_nearPlane = _value;
				m_frustum.setCamInternals(glm::radians((float)m_fov), Window::getAspect(), m_nearPlane, m_farPlane);
		}

		void Camera::setFarPlane(float _value)
		{
				m_farPlane = _value;
				m_frustum.setCamInternals(glm::radians((float)m_fov), Window::getAspect(), m_nearPlane, m_farPlane);
		}

		void Camera::setProjectionMatrix(float _fov, float _width, float _height, float _nearP, float _farP)
		{
				resetProjectionMatrix();
				m_perspMatrix = new glm::mat4(glm::perspective(glm::radians(_fov), _width / _height, _nearP, _farP));
				m_frustum.setCamInternals(glm::radians(_fov), _width / _height, _nearP, _farP);
		}

		void Camera::resetProjectionMatrix()
		{
				if (m_perspMatrix)
				{
						delete m_perspMatrix;
						m_perspMatrix = nullptr;
				}
		}

		glm::mat4 Camera::getProjectionMatrix() const noexcept
		{
				if (m_perspMatrix)
				{
						return *m_perspMatrix;
				}
				if (m_ortho)
				{
						return glm::ortho(0.0f, (float)Window::getWidth() * m_size,
								0.0f, (float)Window::getHeight() * m_size, m_nearPlane, m_farPlane);
				}
				else
				{
						return glm::perspective(glm::radians((float)m_fov),
								Window::getAspect(), m_nearPlane, m_farPlane);
				}
		}

		const glm::mat4 & Camera::getViewMatrix() const noexcept
		{
				return m_viewMatrix;
		}

		void Camera::renderSkybox()
		{
				if (m_skybox)
				{
						m_skybox->render();
				}
		}

		void Camera::updateView()
		{
				refreshInternalTransform();

				m_viewMatrix = glm::inverse(m_transform->worldTransform());

				m_frustum.update(m_transform->worldPosition(),
						m_transform->worldForwardAxis(),
						m_transform->worldRightAxis(),
						m_transform->worldUpAxis());
		}
		void Camera::refreshInternalTransform()
		{
				m_oldTransform.setWorldPosition(m_transform->worldPosition());
				m_oldTransform.setWorldOrientation(m_transform->worldScale());
				m_oldTransform.setWorldScale(m_transform->worldScale());
		}
}