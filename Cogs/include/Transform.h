#pragma once

#include "Component.h"

#include <vector>
#include "../../dependencies/include/glm/gtc/quaternion.hpp"

namespace cogs
{
		class Transform : public Component
		{
		private:
				Transform* m_parent{ nullptr }; ///< the parent transform of this transform
				std::vector<Transform*> m_children;

				glm::vec3 m_localPosition{ 0.0f, 0.0f, 0.0f }; ///< local position
				glm::vec3 m_localScale{ 1.0f, 1.0f, 1.0f }; ///< local scale
				glm::vec3 m_localOrientation{ 0.0f, 0.0f, 0.0f }; ///< local orientation in euler angles in radians
				glm::quat m_localOrientationRaw{ glm::vec3(0.0f, 0.0f, 0.0f) }; ///< local orientation as a quaternion

				void detachChildren();
		public:
				Transform();
				~Transform();

				Transform* getParent()											const noexcept;
				std::vector<Transform*>& getChildren() noexcept;

				void setParent(Transform* _parent);

				void rotate(const glm::vec3& _eulerAngles);
				void rotate(float _x, float _y, float _z);

				void rotate(const glm::vec3& _axis, float _angle);
				void rotate(float _x, float _y, float _z, float _angle);

				void rotate(const glm::quat& _rotationQuat);

				void translate(const glm::vec3& _offset);
				void translate(float _x, float _y, float _z);

				void offsetScale(const glm::vec3& _offset);
				void offsetScale(float _x, float _y, float _z);

				/**
				*	\brief returns the local space position
				*/
				const glm::vec3& localPosition()	const noexcept;

				/**
				*	\brief returns the local space orientation in euler angles (radians)
				*/
				const glm::vec3& localOrientation() const noexcept;

				/**
				*	\brief returns the local space scale
				*/
				const glm::vec3& localScale() const noexcept;

				/**
				*	\brief returns the local space model matrix
				*/
				glm::mat4 localTransform()	const;

				/**
				*	\brief returns the world space position
				*/
				glm::vec3 worldPosition() const noexcept;

				/**
				*	\brief returns the world space orientation in euler angles (radians)
				*/
				glm::vec3 worldOrientation() const noexcept;

				/**
				*	\brief returns the world space orientation as a quat
				*/
				glm::quat worldOrientationRaw() const noexcept;

				/**
				*	\brief returns the world space scale
				*/
				glm::vec3 worldScale()	const noexcept;

				/**
				*	\brief returns the world space model matrix
				*/
				glm::mat4 worldTransform() const;

				/**
				*	\brief Returns the right axis using the local space coordinates (direction to the right (positive x axis))
				*/
				glm::vec3 localRightAxis() const noexcept;

				/**
				*	\brief Returns the up axis using the local space coordinates (direction pointing up (positive y axis))
				*/
				glm::vec3 localUpAxis()	const noexcept;

				/**
				*	\brief Returns the forward axis using the local space coordinates
				* (direction pointing forwards (to the negative z axis as opengl is using right handed coordinate system))
				*/
				glm::vec3 localForwardAxis() const noexcept;

				/**
				*	\brief Returns the right axis using the world space coordinates (direction to the right (positive x axis))
				*/
				glm::vec3 worldRightAxis() const noexcept;

				/**
				*	\brief Returns the up axis using the world space coordinates (direction pointing up (positive y axis))
				*/
				glm::vec3 worldUpAxis()	const noexcept;

				/**
				*	\brief Returns the forward axis using the world space coordinates
				* (direction pointing forwards (to the negative z axis as opengl is using right handed coordinate system))
				*/
				glm::vec3 worldForwardAxis() const noexcept;

				/**
				*	\brief setters for local transform
				*/
				void setLocalOrientation(const glm::quat& _value);
				void setLocalOrientation(const glm::vec3& _value);
				void setLocalPosition(const glm::vec3& _value);
				void setLocalScale(const glm::vec3& _value);

				/**
				*	\brief setters for world transform
				*/
				void setWorldOrientation(const glm::quat& _value);
				void setWorldOrientation(const glm::vec3& _value);
				void setWorldPosition(const glm::vec3& _value);
				void setWorldScale(const glm::vec3& _value);

				bool Transform::operator==(const Transform & _rhs) const;
		};
}