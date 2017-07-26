#include <iostream>

#include <Cogs\include\Application.h>
#include <Cogs\include\BulletDebugRenderer.h>

#include "../include/TestScene.h"
#include "../include/MainMenuScene.h"

//#include <Cogs\include\EntityManager.h>
//#include <Cogs\include\Window.h>
//#include <Cogs\include\Timing.h>
//#include <Cogs\include\Camera.h>
//#include <Cogs\include\Renderer2D.h>
//#include <Cogs\include\Renderer3D.h>
//#include <Cogs\include\SpriteRenderer.h>
//#include <Cogs\include\ResourceManager.h>
//#include <Cogs\include\Material.h>
//#include <Cogs\include\Input.h>
//#include <Cogs\include\Framebuffer.h>
//#include <Cogs\include\Physics.h>
//#include <Cogs\include\BulletDebugRenderer.h>
//#include <Cogs\include\MeshRenderer.h>
//#include <Cogs\include\BoxCollider.h>
//#include <Cogs\include\RigidBody.h>
//#include <Cogs\include\SphereCollider.h>
//#include <Cogs\include\FPSCameraControl.h>
//#include <Cogs\include\Skybox.h>
//#include <Cogs\include\Button.h>

//class SpriteController : public cogs::Component
//{
//protected:
//		float m_speed;
//
//		void update(float _deltaTime)
//		{
//				if (cogs::Input::isKeyDown(cogs::KeyCode::Q))
//				{
//						m_entity->transform()->rotate(0.0f, 0.0f, glm::radians(m_speed * _deltaTime));
//				}
//				if (cogs::Input::isKeyDown(cogs::KeyCode::E))
//				{
//						m_entity->transform()->rotate(0.0f, 0.0f, glm::radians(-m_speed * _deltaTime));
//				}
//				if (cogs::Input::isKeyDown(cogs::KeyCode::A))
//				{
//						m_entity->transform()->translate(-m_speed * _deltaTime, 0.0f, 0.0f);
//				}
//				if (cogs::Input::isKeyDown(cogs::KeyCode::D))
//				{
//						m_entity->transform()->translate(m_speed * _deltaTime, 0.0f, 0.0f);
//				}
//				if (cogs::Input::isKeyDown(cogs::KeyCode::W))
//				{
//						m_entity->transform()->translate(0.0f, m_speed * _deltaTime, 0.0f);
//				}
//				if (cogs::Input::isKeyDown(cogs::KeyCode::S))
//				{
//						m_entity->transform()->translate(0.0f, -m_speed * _deltaTime, 0.0f);
//				}
//		}
//public:
//		SpriteController(float _speed): m_speed(_speed)
//		{
//		}
//		~SpriteController()
//		{
//		}
//};
//
//class PaddleController : public cogs::Component
//{
//protected:
//		cogs::RigidBody* m_rb{ nullptr }; ///< the paddle's rigidbody
//		float m_moveSpeed{ 0.0f }; ///< the movespeed of the paddle
//
//		void init() override
//		{
//				m_rb = m_entity->getComponent<cogs::RigidBody>();
//		}
//
//		void update(float _deltaTime) override
//		{
//				//don't let the paddle accelerate over time from the force applied to it
//				//as the force should apply for only 1 frame to keep it well-controlled
//				m_rb->setLinearVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
//
//				if (cogs::Input::isKeyDown(cogs::KeyCode::LEFT))
//				{
//						m_rb->applyCentralForce(glm::vec3(-m_moveSpeed * _deltaTime, 0.0f, 0.0f));
//				}
//				if (cogs::Input::isKeyDown(cogs::KeyCode::RIGHT))
//				{
//						m_rb->applyCentralForce(glm::vec3(m_moveSpeed * _deltaTime, 0.0f, 0.0f));
//				}
//		}
//public:
//		PaddleController(float _moveSpeed) : m_moveSpeed(_moveSpeed) {}
//		~PaddleController() {}
//};
//
//class BallBehavior : public cogs::Component
//{
//protected:
//		cogs::RigidBody* m_rb{ nullptr }; ///< the rigidbody of the ball
//		float m_desiredVelocity{ 0.0f }; ///< the desired velocity of the ball
//
//		/**
//		* \brief The initialize component function
//		*/
//		void init() override
//		{
//				m_rb = m_entity->getComponent<cogs::RigidBody>();
//		}
//
//		/**
//		* \brief The update component function
//		*/
//		void update(float _deltaTime) override
//		{
//				if (m_rb->getActivationState() == 5)
//				{
//						if (cogs::Input::isKeyPressed(cogs::KeyCode::SPACE))
//						{
//								m_rb->setActivationState(1);
//								m_rb->setLinearVelocity(glm::vec3(20.0f, 20.0f, 0.0f));
//								const btVector3& desiredVelocity = m_rb->getRigidBody()->getLinearVelocity();
//								m_desiredVelocity = desiredVelocity.length();
//						}
//				}
//				else
//				{
//						btVector3 currentVelocityDirection = m_rb->getRigidBody()->getLinearVelocity();
//						float currentVelocty = currentVelocityDirection.length();
//						if (currentVelocty < m_desiredVelocity)
//						{
//								currentVelocityDirection *= (m_desiredVelocity / currentVelocty);
//								m_rb->setLinearVelocity(glm::vec3(currentVelocityDirection.x(), currentVelocityDirection.y(), currentVelocityDirection.z()));
//						}
//				}
//		}
//
//		/**
//		* \brief handle collisions of the ball
//		*/
//		void onCollision(const glm::vec3& _pointA,
//				const glm::vec3& _pointB,
//				const glm::vec3& _normalOnB,
//				cogs::Entity* _other) override
//		{
//				const std::string& otherTag = _other->getTag();
//
//				if (otherTag == "brick")
//				{
//						_other->destroy();
//				}
//				else if (otherTag == "ground")
//				{
//						m_entity->destroy();
//				}
//		}
//
//public:
//		BallBehavior() {}
//		~BallBehavior() {}
//};

#undef main

struct Test1
{
		bool m_running{ false }; // 1
		cogs::Renderer2D m_renderer2D; //68
		cogs::ParticleRenderer m_particleRenderer; //68
		cogs::Renderer3D m_renderer3D; //44
		cogs::SceneManager m_sceneManager; //24
		cogs::Physics m_physics; //48
		cogs::EntityManager m_entityManager; //16
		cogs::BulletDebugRenderer m_debugRenderer; //60
		cogs::FpsLimiter m_fpsLimiter; //40
		cogs::ResourceManager m_resourceManager; //16
		cogs::Window m_window; //40
};

struct Test2
{
		cogs::Window m_window;																 			 //40
		cogs::FpsLimiter m_fpsLimiter;												 //40
		cogs::SceneManager m_sceneManager;								 //24
		cogs::EntityManager m_entityManager;						 //16
		cogs::Renderer2D m_renderer2D;												 //68
		cogs::Renderer3D m_renderer3D;												 //44
		cogs::Physics m_physics;																		 //48
		cogs::ResourceManager m_resourceManager;			//16
		cogs::ParticleRenderer m_particleRenderer; //68
		cogs::BulletDebugRenderer m_debugRenderer; //60
		bool m_running;																											 // 1
};

int main(int argc, char** argv)
{
		std::cout << sizeof(cogs::Window) << std::endl;
		std::cout << sizeof(cogs::FpsLimiter) << std::endl;
		std::cout << sizeof(cogs::SceneManager) << std::endl;
		std::cout << sizeof(cogs::EntityManager) << std::endl;
		std::cout << sizeof(cogs::Renderer2D) << std::endl;
		std::cout << sizeof(cogs::Renderer3D) << std::endl;
		std::cout << sizeof(cogs::Physics) << std::endl;
		std::cout << sizeof(cogs::ResourceManager) << std::endl;
		std::cout << sizeof(cogs::ParticleRenderer) << std::endl;
		std::cout << sizeof(cogs::BulletDebugRenderer) << std::endl;
		std::cout << sizeof(Test1) << std::endl;
		std::cout << sizeof(Test2) << std::endl;



		//cogs::Application app;

		//app.addScene(std::make_unique<MainMenu>(&app));
		//app.addScene(std::make_unique<TestScene>(&app));

		//app.run("Test", 1024, 576);
		std::cin.get();
		return 0;
}