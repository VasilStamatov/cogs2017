#include "../include/RigidBody.h"

#include "../include/Entity.h"

#include "../include/CMotionState.h"
#include "../include/Physics.h"

#include "../include/BoxCollider.h"
#include "../include/SphereCollider.h"
#include "../include/CapsuleCollider.h"
#include "../include/ConeCollider.h"
#include "../include/CylinderCollider.h"

#include <glm\gtc\type_ptr.hpp>

namespace cogs
{
		RigidBody::RigidBody(Physics* _physicsWorld, float _mass, bool _isKinematic) :
				m_mass(_mass), m_isKinematic(_isKinematic), m_physicsWorld(_physicsWorld)
		{
				btClamp(m_mass, 0.0f, 1.0f);
		}

		RigidBody::~RigidBody()
		{
				m_physicsWorld->removeRigidBody(m_rigidBody.get());
		}

		void RigidBody::init()
		{
				m_motionState = std::make_unique<CMotionState>(m_entity->transform());

				btVector3 intertia(0.0f, 0.0f, 0.0f);

				Collider* colliderShape;

				if (m_entity->hasComponent<BoxCollider>())
				{
						colliderShape = m_entity->getComponent<BoxCollider>();
				}
				else if (m_entity->hasComponent<SphereCollider>())
				{
						colliderShape = m_entity->getComponent<SphereCollider>();
				}
				else if (m_entity->hasComponent<CapsuleCollider>())
				{
						colliderShape = m_entity->getComponent<CapsuleCollider>();
				}
				else if (m_entity->hasComponent<ConeCollider>())
				{
						colliderShape = m_entity->getComponent<ConeCollider>();
				}
				else if (m_entity->hasComponent<CylinderCollider>())
				{
						colliderShape = m_entity->getComponent<CylinderCollider>();
				}

				if (m_mass != 0.0f)
				{
						colliderShape->getShape()->calculateLocalInertia(m_mass, intertia);
				}

				btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(m_mass, m_motionState.get(), colliderShape->getShape(), intertia);

				m_rigidBody = std::make_unique<btRigidBody>(rigidBodyCI);

				if (m_isKinematic)
				{
						m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
				}

				m_physicsWorld->addRigidBody(m_rigidBody.get());

				m_rigidBody->setUserPointer(m_entity);
		}

		void RigidBody::translate(const glm::vec3 & _offset)
		{
				m_rigidBody->translate(btVector3(_offset.x, _offset.y, _offset.z));
		}
		void RigidBody::applyCentralForce(const glm::vec3 & _force)
		{
				m_rigidBody->applyCentralForce(btVector3(_force.x, _force.y, _force.z));
		}
		void RigidBody::applyForce(const glm::vec3 & _force, const glm::vec3 & _relativePos)
		{
				m_rigidBody->applyForce(btVector3(_force.x, _force.y, _force.z), btVector3(_relativePos.x, _relativePos.y, _relativePos.z));
		}
		void RigidBody::setLinearVelocity(const glm::vec3 & _offset)
		{
				m_rigidBody->setLinearVelocity(btVector3(_offset.x, _offset.y, _offset.z));
		}
		void RigidBody::setAngularVelocity(const glm::vec3 & _offset)
		{
				m_rigidBody->setAngularVelocity(btVector3(_offset.x, _offset.y, _offset.z));
		}
		void RigidBody::setRestitution(float _restitution)
		{
				m_rigidBody->setRestitution(_restitution);
		}
		void RigidBody::setFriction(float _friction)
		{
				m_rigidBody->setFriction(_friction);
		}
		void RigidBody::setLinearFactor(const glm::vec3 & _offset)
		{
				m_rigidBody->setLinearFactor(btVector3(_offset.x, _offset.y, _offset.z));
		}
		void RigidBody::setAngularFactor(const glm::vec3 & _offset)
		{
				m_rigidBody->setAngularFactor(btVector3(_offset.x, _offset.y, _offset.z));
		}
		void RigidBody::setDamping(float _x, float _y)
		{
				m_rigidBody->setDamping(_x, _y);
		}
		void RigidBody::setWorldTransform()
		{
				btTransform temp;
				temp.setFromOpenGLMatrix(glm::value_ptr(m_entity->transform()->worldTransform()));
				m_rigidBody->setWorldTransform(temp);
		}
		void RigidBody::activate()
		{
				m_rigidBody->activate();
		}
		void RigidBody::setActivationState(int _state)
		{
				m_rigidBody->forceActivationState(_state);
		}
}