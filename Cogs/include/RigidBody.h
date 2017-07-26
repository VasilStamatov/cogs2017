#pragma once

#include "Component.h"
#include <Bullet/btBulletDynamicsCommon.h>
#include <memory>

namespace cogs
{
		class Physics;
		class CMotionState;
		/**
		* This component, given to an entity will give it a rigidbody,
		constructed from information that should already exist in the entity such as collider shape,
		and will add it to the physics world
		*/
		class RigidBody : public Component
		{
		public:
				RigidBody(Physics* _physicsWorld, float _mass = 1.0f, bool _isKinematic = false);
				~RigidBody();

				/**
				* Translates the body by a certain amount
				*/
				void translate(const glm::vec3& _offset);

				/**
				* applies a force to the origin of the body
				*/
				void applyCentralForce(const glm::vec3& _force);

				/**
				* applies a force to the body from a specific relative position
				*/
				void applyForce(const glm::vec3& _force, const glm::vec3 & _relativePos);

				/**
				* Makes the rigid body move
				*/
				void setLinearVelocity(const glm::vec3& _offset);

				/**
				* Makes the rigid body spin
				*/
				void setAngularVelocity(const glm::vec3& _offset);

				/**
				* The spring or bounciness of a rigid body
				* 0 = doesn't bounce at all
				* between 0 and 1 = the object bounces, but with each bounce loses part of its energy
				* over 1 = the object gains energy with each bounce
				*/
				void setRestitution(float _restitution);

				/**
				* The friction of a rigid body
				*/
				void setFriction(float _friction);

				/**
				* Locks linear movement to specific axis
				*/
				void setLinearFactor(const glm::vec3& _offset);

				/**
				* Locks angular movement to specific axis
				*/
				void setAngularFactor(const glm::vec3& _offset);

				void setDamping(float _x, float _y);

				void setWorldTransform();

				void activate();

				/**
				* Sets the activation state of the rigidbody
				* \param _state - the state the rigid body can be set to:
				* http://www.bulletphysics.org/mediawiki-1.5.8/index.php/Activation_States
				* ACTIVE_TAG										 = 1 -> better use activate();
				* ISLAND_SLEEPING					 = 2 -> you probably don't want or need to set this one manually.
				* WANTS_DEACTIVATION		 = 3 -> you probably don't want or need to set this one manually.
				* DISABLE_DEACTIVATION = 4 -> makes a body active forever, used for something like a player-controlled object
				* DISABLE_SIMULATION		 = 5 -> Does the opposite, making a body deactivated forever
				*/
				void setActivationState(int _state);

				int getActivationState() const { return m_rigidBody->getActivationState(); }

				btRigidBody* getRigidBody() { return m_rigidBody.get(); }

		protected:
				void init() override;

		private:
				std::unique_ptr<btRigidBody> m_rigidBody{ nullptr }; ///< the rigid body that bullet uses
				std::unique_ptr<CMotionState> m_motionState{ nullptr }; ///< motion state implementation for this engine
				Physics* m_physicsWorld; ///< the world this rigidbody belongs to
				float m_mass{ 0.0f }; ///< the mass of this rigid body
				bool m_isKinematic{ false }; ///< flag wether this body is kinematic or not
		};
}