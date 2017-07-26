#pragma once

#include "Component.h"

#include <vector>
#include "../../dependencies/include/glm/gtc/quaternion.hpp"

namespace cogs
{
		class Transform : public Component
		{
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

				const glm::vec3& localPosition()							const noexcept;
				const glm::vec3& localOrientation()				const noexcept;
				const glm::quat& localOrientationRaw() const noexcept;
				const glm::vec3& localScale()										const noexcept;
				glm::mat4 localTransform()													const;

				glm::vec3 worldPosition()							const noexcept;
				glm::vec3 worldOrientation()				const noexcept;
				glm::quat worldOrientationRaw() const noexcept;
				glm::vec3 worldScale()										const noexcept;
				glm::mat4 worldTransform()				  const;

				glm::vec3 localRightAxis()		 const noexcept;
				glm::vec3 localUpAxis()					 const noexcept;
				glm::vec3 localForwardAxis() const noexcept;

				glm::vec3 worldRightAxis()		 const noexcept;
				glm::vec3 worldUpAxis()					 const noexcept;
				glm::vec3 worldForwardAxis() const noexcept;

				void setLocalOrientation(const glm::quat& _value);
				void setLocalOrientation(const glm::vec3& _value);
				void setLocalPosition(const glm::vec3& _value);
				void setLocalScale(const glm::vec3& _value);

				void setWorldOrientation(const glm::quat& _value);
				void setWorldOrientation(const glm::vec3& _value);
				void setWorldPosition(const glm::vec3& _value);
				void setWorldScale(const glm::vec3& _value);

				bool operator==(const Transform & _rhs) const;

		private:
				void detachChildren();
				
		private:
				std::vector<Transform*> m_children;
				glm::quat m_localOrientationRaw{ glm::vec3(0.0f, 0.0f, 0.0f) };
				glm::vec3 m_localPosition{ 0.0f, 0.0f, 0.0f };
				glm::vec3 m_localScale{ 1.0f, 1.0f, 1.0f };
				glm::vec3 m_localOrientation{ 0.0f, 0.0f, 0.0f };
				Transform* m_parent{ nullptr };
		};
}