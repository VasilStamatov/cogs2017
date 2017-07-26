#include "../include/TestScene.h"

#include <Cogs\include\Application.h>
#include <Cogs\include\ResourceManager.h>
#include <Cogs\include\Material.h>
#include <Cogs\include\Framebuffer.h>
#include <Cogs\include\MeshRenderer.h>
#include <Cogs\include\BoxCollider.h>
#include <Cogs\include\RigidBody.h>
#include <Cogs\include\SphereCollider.h>
#include <Cogs\include\FPSCameraControl.h>
#include <Cogs\include\Skybox.h>
#include <Cogs\include\Button.h>
#include <Cogs\include\Camera.h>
#include <Cogs\include\Input.h>
#include <Cogs\include\Mesh.h>
#include <Cogs\include\GLCubemapTexture.h>

class SpriteController : public cogs::Component
{
protected:
		float m_speed;

		void update(float _deltaTime)
		{
				if (cogs::Input::isKeyDown(cogs::KeyCode::Q))
				{
						m_entity->transform()->rotate(0.0f, 0.0f, glm::radians(m_speed * _deltaTime));
				}
				if (cogs::Input::isKeyDown(cogs::KeyCode::E))
				{
						m_entity->transform()->rotate(0.0f, 0.0f, glm::radians(-m_speed * _deltaTime));
				}
				if (cogs::Input::isKeyDown(cogs::KeyCode::A))
				{
						m_entity->transform()->translate(-m_speed * _deltaTime, 0.0f, 0.0f);
				}
				if (cogs::Input::isKeyDown(cogs::KeyCode::D))
				{
						m_entity->transform()->translate(m_speed * _deltaTime, 0.0f, 0.0f);
				}
				if (cogs::Input::isKeyDown(cogs::KeyCode::W))
				{
						m_entity->transform()->translate(0.0f, m_speed * _deltaTime, 0.0f);
				}
				if (cogs::Input::isKeyDown(cogs::KeyCode::S))
				{
						m_entity->transform()->translate(0.0f, -m_speed * _deltaTime, 0.0f);
				}
		}
public:
		SpriteController(float _speed): m_speed(_speed)
		{
		}
		~SpriteController()
		{
		}
};

class PaddleController : public cogs::Component
{
protected:
		cogs::RigidBody* m_rb{ nullptr }; ///< the paddle's rigidbody
		float m_moveSpeed{ 0.0f }; ///< the movespeed of the paddle

		void init() override
		{
				m_rb = m_entity->getComponent<cogs::RigidBody>();
		}

		void update(float _deltaTime) override
		{
				//don't let the paddle accelerate over time from the force applied to it
				//as the force should apply for only 1 frame to keep it well-controlled
				m_rb->setLinearVelocity(glm::vec3(0.0f, 0.0f, 0.0f));

				if (cogs::Input::isKeyDown(cogs::KeyCode::LEFT))
				{
						m_rb->applyCentralForce(glm::vec3(-m_moveSpeed * _deltaTime, 0.0f, 0.0f));
				}
				if (cogs::Input::isKeyDown(cogs::KeyCode::RIGHT))
				{
						m_rb->applyCentralForce(glm::vec3(m_moveSpeed * _deltaTime, 0.0f, 0.0f));
				}
		}
public:
		PaddleController(float _moveSpeed) : m_moveSpeed(_moveSpeed) {}
		~PaddleController() {}
};

class BallBehavior : public cogs::Component
{
protected:
		cogs::RigidBody* m_rb{ nullptr }; ///< the rigidbody of the ball
		float m_desiredVelocity{ 0.0f }; ///< the desired velocity of the ball

		/**
		* \brief The initialize component function
		*/
		void init() override
		{
				m_rb = m_entity->getComponent<cogs::RigidBody>();
		}

		/**
		* \brief The update component function
		*/
		void update(float _deltaTime) override
		{
				if (m_rb->getActivationState() == 5)
				{
						if (cogs::Input::isKeyPressed(cogs::KeyCode::SPACE))
						{
								m_rb->setActivationState(1);
								m_rb->setLinearVelocity(glm::vec3(20.0f, 20.0f, 0.0f));
								const btVector3& desiredVelocity = m_rb->getRigidBody()->getLinearVelocity();
								m_desiredVelocity = desiredVelocity.length();
						}
				}
				else
				{
						btVector3 currentVelocityDirection = m_rb->getRigidBody()->getLinearVelocity();
						float currentVelocty = currentVelocityDirection.length();
						if (currentVelocty < m_desiredVelocity)
						{
								currentVelocityDirection *= (m_desiredVelocity / currentVelocty);
								m_rb->setLinearVelocity(glm::vec3(currentVelocityDirection.x(), currentVelocityDirection.y(), currentVelocityDirection.z()));
						}
				}
		}

		/**
		* \brief handle collisions of the ball
		*/
		void onCollision(const glm::vec3& _pointA,
				const glm::vec3& _pointB,
				const glm::vec3& _normalOnB,
				cogs::Entity* _other) override
		{
				const std::string& otherTag = _other->getTag();

				if (otherTag == "brick")
				{
						_other->destroy();
				}
				else if (otherTag == "ground")
				{
						m_entity->destroy();
				}
		}

public:
		BallBehavior() {}
		~BallBehavior() {}
};


TestScene::TestScene(cogs::Application* _app) : Scene(_app)
{
		setName("TestScene");
}

TestScene::~TestScene()
{
}

void TestScene::OnEntry()
{
		std::vector<std::string> skyboxFilenames(6);
		skyboxFilenames.at(0) = "Textures/space/cwd_rt.jpg";
		skyboxFilenames.at(1) = "Textures/space/cwd_lf.jpg";
		skyboxFilenames.at(2) = "Textures/space/cwd_up.jpg";
		skyboxFilenames.at(3) = "Textures/space/cwd_dn.jpg";
		skyboxFilenames.at(4) = "Textures/space/cwd_bk.jpg";
		skyboxFilenames.at(5) = "Textures/space/cwd_ft.jpg";

		cogs::ResourceManager* rm = getResourceManager();

		cogs::Skybox* testSkybox = rm->get<cogs::Skybox>("TestSkybox", rm,
				rm->get<cogs::GLSLProgram>("SkyboxShader", "Shaders/Skybox.vs", "Shaders/Skybox.fs"),
				rm->get<cogs::GLCubemapTexture>("skyboxTexture", skyboxFilenames), true);

		cogs::Entity* mainCamera = createEntity("MainCamera");
		mainCamera->transform()->translate(glm::vec3(0.0f, 0.0f, 55.0f));
		mainCamera->addComponent<cogs::FPSCameraControl>(50.0f);
		cogs::Camera* cam = mainCamera->addComponent<cogs::Camera>();
		//cam->setBackgroundColor(cogs::Color::black);
		cam->setProjectionType(false);
		cam->setSkybox(testSkybox);

		cogs::Entity* exitButton = createEntity("Exit");
		exitButton->addComponent<cogs::Button>("Exit", glm::vec4(0.0f), glm::vec4(10.0f, 10.0f, 80.0f, 40.0f));
		exitButton->getComponent<cogs::Button>()->addEvent([this](const CEGUI::EventArgs&) { exitApplication(); return true; });

		cogs::Entity* paddle = createEntity("PlayerPaddle");
		paddle->setTag("Paddle");
		paddle->addComponent<cogs::MeshRenderer>(rm->get<cogs::Mesh>("Cube", "Models/TestModels/cube.obj", rm), getRenderer3D());
		paddle->transform()->setWorldScale(glm::vec3(2.0f, 0.5f, 1.0f));
		paddle->transform()->translate(glm::vec3(0.0f, -3.0f, 0.0f));
		paddle->addComponent<cogs::BoxCollider>(glm::vec3(2.0f, 0.5f, 1.0f));
		paddle->addComponent<cogs::RigidBody>(getPhysicsWorld(), 1.0f);
		paddle->getComponent<cogs::RigidBody>()->setActivationState(4);
		paddle->getComponent<cogs::RigidBody>()->setLinearFactor(glm::vec3(1.0f, 0.0f, 0.0f));
		paddle->getComponent<cogs::RigidBody>()->setAngularFactor(glm::vec3(0.0f, 0.0f, 0.0f));
		paddle->getComponent<cogs::RigidBody>()->setRestitution(1.0f);
		paddle->addComponent<PaddleController>(150000.0f);

		cogs::Entity* groundBound = createEntity("GroundBoundary");
		groundBound->setTag("ground");
		groundBound->transform()->translate(glm::vec3(-2.5f, -5.0f, 0.0f));
		groundBound->addComponent<cogs::BoxCollider>(glm::vec3(32.5f, 1.0f, 1.0f));
		groundBound->addComponent<cogs::RigidBody>(getPhysicsWorld(), 0.0f);

		cogs::Entity* ceilingBound = createEntity("CeilingBoundary");
		ceilingBound->transform()->translate(glm::vec3(-2.5f, 30.0f, 0.0f));
		ceilingBound->addComponent<cogs::BoxCollider>(glm::vec3(32.5f, 1.0f, 1.0f));
		ceilingBound->addComponent<cogs::RigidBody>(getPhysicsWorld(), 0.0f);
		ceilingBound->getComponent<cogs::RigidBody>()->setRestitution(1.0f);

		cogs::Entity* leftBound = createEntity("LeftBoundary");
		leftBound->transform()->translate(glm::vec3(-36.0f, 12.5f, 0.0f));
		leftBound->addComponent<cogs::BoxCollider>(glm::vec3(1.0f, 16.0f, 1.0f));
		leftBound->addComponent<cogs::RigidBody>(getPhysicsWorld(), 0.0f);
		leftBound->getComponent<cogs::RigidBody>()->setRestitution(1.0f);

		cogs::Entity* rightBound = createEntity("RightBoundary");
		rightBound->transform()->translate(glm::vec3(31, 12.5f, 0.0f));
		rightBound->addComponent<cogs::BoxCollider>(glm::vec3(1.0f, 16.0f, 1.0f));
		rightBound->addComponent<cogs::RigidBody>(getPhysicsWorld(), 0.0f);
		rightBound->getComponent<cogs::RigidBody>()->setRestitution(1.0f);

		cogs::Entity* ball = createEntity("Ball");
		ball->setTag("ball");
		ball->addComponent<cogs::MeshRenderer>(rm->get<cogs::Mesh>("Sphere", "Models/TestModels/sphere.obj", rm), getRenderer3D());
		ball->transform()->translate(glm::vec3(0.0f, 3.0f, 0.0f));
		ball->addComponent<cogs::SphereCollider>(1.0f);
		ball->addComponent<cogs::RigidBody>(getPhysicsWorld(), 1.0f);
		ball->getComponent<cogs::RigidBody>()->setActivationState(5);
		ball->getComponent<cogs::RigidBody>()->setLinearFactor(glm::vec3(1.0f, 1.0f, 0.0f));
		ball->getComponent<cogs::RigidBody>()->setRestitution(1.0f);
		ball->addComponent<BallBehavior>();

		for (int i = -30; i < 30; i += 4)
		{
				for (int j = -10; j < 0; j += 4)
				{
						cogs::Entity* brick = createEntity("Brick");
						brick->setTag("brick");
						brick->addComponent<cogs::MeshRenderer>(rm->get<cogs::Mesh>("Cube", "Models/TestModels/cube.obj", rm), getRenderer3D());
						brick->transform()->translate(glm::vec3(0.0f + i, 30.0f + j, 0.0f));
						brick->addComponent<cogs::BoxCollider>(glm::vec3(1.0f, 1.0f, 1.0f));
						brick->addComponent<cogs::RigidBody>(getPhysicsWorld(), 0.0f);
						brick->getComponent<cogs::RigidBody>()->setActivationState(5);
						brick->getComponent<cogs::RigidBody>()->setRestitution(1.0f);
				}
		}
}
