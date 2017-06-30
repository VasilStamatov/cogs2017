#include "../include/Transform.h"
#include "../include/Entity.h"

#include <glm\gtc\matrix_transform.hpp>

namespace cogs
{
		void Transform::detachChildren()
		{
				while (!m_children.empty())
				{
						Transform* child = m_children.back();
						child->setParent(nullptr);
						child->m_entity->destroy();
				}
		}

		Transform::Transform()
		{
		}

		Transform::~Transform()
		{
				detachChildren();
				if (m_parent)
				{
						setParent(nullptr);
				}
		}

		Transform * Transform::getParent() const noexcept
		{
				return m_parent;
		}
		std::vector<Transform*>& Transform::getChildren() noexcept
		{
				return m_children;
		}

		void Transform::setParent(Transform * _parent)
		{
				if (_parent == this)
				{
						//cannot be parent of yourself 
						return;
				}

				//check if to-be parent is currently a child
				for (size_t i = 0; i < m_children.size(); ++i)
				{
						if (m_children.at(i) == _parent)
						{
								//set the to-be parent to be a child of this entity's parent (null if none)
								m_children.at(i)->setParent(m_parent);
						}
				}

				if (m_parent)
				{
						//if you already have a parent, erase yourself from its vector
						m_parent->m_children.erase(std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this));
				}

				//if to-be parent isn't null, add yourself to its children vector
				if (_parent)
				{
						_parent->m_children.push_back(this);
				}

				setLocalPosition(worldPosition());
				setLocalScale(worldScale());
				setLocalOrientation(worldOrientationRaw());
				//set the parent
				m_parent = _parent;
				setWorldPosition(m_localPosition);
				setWorldScale(m_localScale);
				setWorldOrientation(m_localOrientationRaw);
		}
		void Transform::rotate(const glm::vec3 & _eulerAngles)
		{
				glm::quat toRotate(_eulerAngles);

				setLocalOrientation(toRotate * m_localOrientationRaw);
		}
		void Transform::rotate(float _x, float _y, float _z)
		{
				rotate(glm::vec3(_x, _y, _z));
		}
		void Transform::rotate(const glm::vec3 & _axis, float _angle)
		{
				glm::quat toRotate(glm::angleAxis((_angle), _axis));

				setLocalOrientation(toRotate * m_localOrientationRaw);
		}
		void Transform::rotate(float _x, float _y, float _z, float _angle)
		{
				rotate(glm::vec3(_x, _y, _z), _angle);
		}
		void Transform::rotate(const glm::quat & _rotationQuat)
		{
				setLocalOrientation(_rotationQuat * m_localOrientationRaw);
		}
		void Transform::translate(const glm::vec3 & _offset)
		{
				m_localPosition += _offset;
		}
		void Transform::translate(float _x, float _y, float _z)
		{
				m_localPosition.x += _x;
				m_localPosition.y += _y;
				m_localPosition.z += _z;
		}
		void Transform::offsetScale(const glm::vec3 & _offset)
		{
				m_localScale += _offset;
		}
		void Transform::offsetScale(float _x, float _y, float _z)
		{
				m_localScale.x += _x;
				m_localScale.y += _y;
				m_localScale.z += _z;
		}
		const glm::vec3 & Transform::localPosition() const noexcept
		{
				return m_localPosition;
		}
		const glm::vec3 & Transform::localOrientation() const noexcept
		{
				return m_localOrientation;
		}
		const glm::vec3 & Transform::localScale() const noexcept
		{
				return m_localScale;
		}
		glm::mat4 Transform::localTransform() const
		{
				glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_localPosition);
				glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_localScale);
				glm::mat4 rotation = glm::mat4_cast(m_localOrientationRaw);

				glm::mat4 localTransform = translation * rotation * scale;

				return localTransform;
		}
		glm::vec3 Transform::worldPosition() const noexcept
		{
				glm::mat4 worldTrs = worldTransform();

				return glm::vec3(worldTrs[3]);
		}
		glm::vec3 Transform::worldOrientation() const noexcept
		{
				glm::mat4 worldTrs = worldTransform();

				return glm::eulerAngles(glm::quat(worldTrs));
		}
		glm::quat Transform::worldOrientationRaw() const noexcept
		{
				glm::mat4 worldTrs = worldTransform();

				return glm::quat(worldTrs);
		}
		glm::vec3 Transform::worldScale() const noexcept
		{
				glm::mat4 worldTrs = worldTransform();

				return glm::vec3(worldTrs[0][0], worldTrs[1][1], worldTrs[2][2]);
		}
		glm::mat4 Transform::worldTransform() const
		{
				glm::mat4 worldTrans = localTransform();

				if (m_parent)
				{
						worldTrans = m_parent->worldTransform() * worldTrans;
				}

				return worldTrans;
		}
		glm::vec3 Transform::localRightAxis() const noexcept
		{
				return m_localOrientationRaw * glm::vec3(1.0f, 0.0f, 0.0f);
		}
		glm::vec3 Transform::localUpAxis() const noexcept
		{
				return m_localOrientationRaw * glm::vec3(0.0f, 1.0f, 0.0f);
		}
		glm::vec3 Transform::localForwardAxis() const noexcept
		{
				return m_localOrientationRaw * glm::vec3(0.0f, 0.0f, -1.0f);
		}
		glm::vec3 Transform::worldRightAxis() const noexcept
		{
				return worldOrientationRaw() * glm::vec3(1.0f, 0.0f, 0.0f);
		}
		glm::vec3 Transform::worldUpAxis() const noexcept
		{
				return worldOrientationRaw() * glm::vec3(0.0f, 1.0f, 0.0f);
		}
		glm::vec3 Transform::worldForwardAxis() const noexcept
		{
				return worldOrientationRaw() * glm::vec3(0.0f, 0.0f, -1.0f);
		}
		void Transform::setLocalOrientation(const glm::quat & _value)
		{
				//set the raw orientation value
				m_localOrientationRaw = glm::normalize(_value);

				//set the orientation's euler angles representation
				m_localOrientation = glm::eulerAngles(m_localOrientationRaw);
		}
		void Transform::setLocalOrientation(const glm::vec3 & _value)
		{
				setLocalOrientation(glm::quat(_value));
		}
		void Transform::setLocalPosition(const glm::vec3 & _value)
		{
				m_localPosition = _value;
		}
		void Transform::setLocalScale(const glm::vec3 & _value)
		{
				m_localScale = _value;
		}
		void Transform::setWorldOrientation(const glm::quat & _value)
		{
				// set the raw orientation value
				glm::quat worldOrient = glm::normalize(_value);

				//update the local orientation to be correct
				if (m_parent)
				{
						//to get the correct local orientation, multiply the child's world rotation by the parent's conjugate
						m_localOrientationRaw = worldOrient * glm::normalize(glm::conjugate(m_parent->worldOrientationRaw()));
				}
				else
				{
						//if there is no parent, world == local
						m_localOrientationRaw = worldOrient;
				}

				//set the local orientation's euler angle representation
				m_localOrientation = glm::eulerAngles(m_localOrientationRaw);
		}
		void Transform::setWorldOrientation(const glm::vec3 & _value)
		{
				setWorldOrientation(glm::quat(_value));
		}
		void Transform::setWorldPosition(const glm::vec3 & _value)
		{
				//update the local position to be correct
				if (m_parent)
				{
						//to get the correct local position, subtract the parent's world translation from the child's world translation
						m_localPosition = _value - m_parent->worldPosition();
				}
				else
				{
						//if there is no parent, world == local
						m_localPosition = _value;
				}
		}
		void Transform::setWorldScale(const glm::vec3 & _value)
		{
				//update the local scale to be correct
				if (m_parent)
				{
						//to get the correct local scale, multiply the child's world scale with the reciprocal of the parent's world scale
						m_localScale = _value * (1.0f / m_parent->worldScale());
				}
				else
				{
						//if there is no parent, world == local
						m_localScale = _value;
				}
		}
		bool Transform::operator==(const Transform & _rhs) const
		{
				auto boolVec = glm::equal(worldPosition(), _rhs.worldPosition());

				if ((boolVec.x == true) && (boolVec.y == true) && (boolVec.z == true))
				{
						boolVec = glm::equal(worldScale(), _rhs.worldScale());

						if ((boolVec.x == true) && (boolVec.y == true) && (boolVec.z == true))
						{
								boolVec = glm::equal(worldOrientation(), _rhs.worldOrientation());

								if ((boolVec.x == true) && (boolVec.y == true) && (boolVec.z == true))
								{
										return true;
								}
						}
				}
				return false;
		}
}