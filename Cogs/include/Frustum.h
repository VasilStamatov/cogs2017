#pragma once

#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

namespace cogs
{
		class Frustum
		{
				enum class Planes : unsigned int
				{
						Right,
						Left,
						Bottom,
						Top,
						Far,
						Near,

						PlanesCount
				};

				struct Plane
				{
						glm::vec3 normal;
						float d;

						void setNormalAndPoint(const glm::vec3& _normal, const glm::vec3& _point);
						void set3Points(const glm::vec3& _v1, const glm::vec3& _v2, const glm::vec3& _v3);
						void setCoefficients(float _a, float _b, float _c, float _d);
						float distance(const glm::vec3& _p) const;
				};

		public:
				Frustum() {}
				~Frustum() {}

				/**
				* \brief Sets internal camera properties. Needed for update()
				*/
				void setCamInternals(float _fov, float _aspectRatio, float _znear, float _zfar);

				/**
				* \brief Updates the frustum with the geometric information
				* \param[in] _position - the camera's world-space position
				* \param[in] _forward - the camera's world-space forward vector
				* \param[in] _forward - the camera's world-space right vector
				* \param[in] _up - the camera's world-space up vector
				*/
				void update(const glm::vec3& _position,
						const glm::vec3& _forward,
						const glm::vec3& _right,
						const glm::vec3& _up);

				bool pointInFrustum(const glm::vec3& _pos) const;
				bool sphereInFrustum(const glm::vec3& _pos, float _radius) const;

		private:
				glm::vec3 m_nearCenter;
				glm::vec3 m_farCenter;

				glm::vec3 m_nearTopLeft;
				glm::vec3 m_nearBottomLeft;
				glm::vec3 m_nearTopRight;
				glm::vec3 m_nearBottomRight;

				glm::vec3 m_farTopLeft;
				glm::vec3 m_farBottomLeft;
				glm::vec3 m_farTopRight;
				glm::vec3 m_farBottomRight;

				Plane m_planes[static_cast<unsigned int>(Planes::PlanesCount)];
				
				float m_fov{ 0 };
				float m_aspectRatio{ 0.0f };
				float m_znear{ 0.0f };
				float m_zfar{ 0.0f };
				float m_nearHeight{ 0.0f };
				float m_nearWidth{ 0.0f };
				float m_farHeight{ 0.0f };
				float m_farWidth{ 0.0f };
		};
}