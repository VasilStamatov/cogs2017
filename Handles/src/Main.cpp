#include <iostream>

#include <Cogs\include\Application.h>

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

int main(int argc, char** argv)
{
		/*cogs::EntityManager manager;
		cogs::Window window;
		window.create("Test", 1024, 576, cogs::WindowCreationFlags::RESIZABLE);
		//window.setRelativeMouseMode(true);

		bool quit{ false };
		bool debugMode{ false };

		cogs::FpsLimiter fpsLimiter(600.0f);

		cogs::GUI::init("GUI");
		cogs::GUI::loadScheme("TaharezLook.scheme");
		cogs::GUI::setFont("DejaVuSans-10");
		cogs::GUI::setMouseCursor("TaharezLook/MouseArrow");
		cogs::GUI::showMouseCursor();
		window.showMouseCursor(false);

		cogs::Physics physicsWorld(0.0f, -9.81f, 0.0f);

		std::vector<std::string> skyboxFilenames(6);
		skyboxFilenames.at(0) = "Textures/space/cwd_rt.jpg";
		skyboxFilenames.at(1) = "Textures/space/cwd_lf.jpg";
		skyboxFilenames.at(2) = "Textures/space/cwd_up.jpg";
		skyboxFilenames.at(3) = "Textures/space/cwd_dn.jpg";
		skyboxFilenames.at(4) = "Textures/space/cwd_bk.jpg";
		skyboxFilenames.at(5) = "Textures/space/cwd_ft.jpg";

		std::unique_ptr<cogs::Skybox> testSkybox = cogs::Skybox::create(
				cogs::ResourceManager::getGLSLProgram("SkyboxShader", "Shaders/Skybox.vs", "Shaders/Skybox.fs"),
				cogs::ResourceManager::getGLCubemap("skyboxTexture", skyboxFilenames), true);

		cogs::Entity* mainCamera = manager.create("MainCamera");
		mainCamera->transform()->translate(glm::vec3(0.0f, 0.0f, 55.0f));
		//mainCamera->addComponent<cogs::FPSCameraControl>(50.0f);
		cogs::Camera* cam = mainCamera->addComponent<cogs::Camera>();
		//cam->setBackgroundColor(cogs::Color::black);
		cam->setProjectionType(false);
		cam->setSkybox(testSkybox.get());

		cogs::Renderer2D renderer2D;
		cogs::Renderer3D renderer3D;

		cogs::Entity* exitButton = manager.create("Exit");
		exitButton->addComponent<cogs::Button>("Exit", 10.0f, 10.0f, 80.0f, 40.0f);
		exitButton->getComponent<cogs::Button>()->addEvent([&quit](const CEGUI::EventArgs&) { quit = true; return true; });

		cogs::Entity* paddle = manager.create("PlayerPaddle");
		paddle->setTag("Paddle");
		paddle->addComponent<cogs::MeshRenderer>(cogs::ResourceManager::getMesh("Models/TestModels/cube.obj"), &renderer3D);
		paddle->transform()->setWorldScale(glm::vec3(2.0f, 0.5f, 1.0f));
		paddle->transform()->translate(glm::vec3(0.0f, -3.0f, 0.0f));
		paddle->addComponent<cogs::BoxCollider>(glm::vec3(2.0f, 0.5f, 1.0f));
		paddle->addComponent<cogs::RigidBody>(&physicsWorld, 1.0f);
		paddle->getComponent<cogs::RigidBody>()->setActivationState(4);
		paddle->getComponent<cogs::RigidBody>()->setLinearFactor(glm::vec3(1.0f, 0.0f, 0.0f));
		paddle->getComponent<cogs::RigidBody>()->setAngularFactor(glm::vec3(0.0f, 0.0f, 0.0f));
		paddle->getComponent<cogs::RigidBody>()->setRestitution(1.0f);
		paddle->addComponent<PaddleController>(150000.0f);

		cogs::Entity* groundBound = manager.create("GroundBoundary");
		groundBound->setTag("ground");
		groundBound->transform()->translate(glm::vec3(-2.5f, -5.0f, 0.0f));
		groundBound->addComponent<cogs::BoxCollider>(glm::vec3(32.5f, 1.0f, 1.0f));
		groundBound->addComponent<cogs::RigidBody>(&physicsWorld, 0.0f);

		cogs::Entity* ceilingBound = manager.create("CeilingBoundary");
		ceilingBound->transform()->translate(glm::vec3(-2.5f, 30.0f, 0.0f));
		ceilingBound->addComponent<cogs::BoxCollider>(glm::vec3(32.5f, 1.0f, 1.0f));
		ceilingBound->addComponent<cogs::RigidBody>(&physicsWorld, 0.0f);
		ceilingBound->getComponent<cogs::RigidBody>()->setRestitution(1.0f);

		cogs::Entity* leftBound = manager.create("LeftBoundary");
		leftBound->transform()->translate(glm::vec3(-36.0f, 12.5f, 0.0f));
		leftBound->addComponent<cogs::BoxCollider>(glm::vec3(1.0f, 16.0f, 1.0f));
		leftBound->addComponent<cogs::RigidBody>(&physicsWorld, 0.0f);
		leftBound->getComponent<cogs::RigidBody>()->setRestitution(1.0f);

		cogs::Entity* rightBound = manager.create("RightBoundary");
		rightBound->transform()->translate(glm::vec3(31, 12.5f, 0.0f));
		rightBound->addComponent<cogs::BoxCollider>(glm::vec3(1.0f, 16.0f, 1.0f));
		rightBound->addComponent<cogs::RigidBody>(&physicsWorld, 0.0f);
		rightBound->getComponent<cogs::RigidBody>()->setRestitution(1.0f);

		cogs::Entity* ball = manager.create("Ball");
		ball->setTag("ball");
		ball->addComponent<cogs::MeshRenderer>(cogs::ResourceManager::getMesh("Models/TestModels/sphere.obj"), &renderer3D);
		ball->transform()->translate(glm::vec3(0.0f, 3.0f, 0.0f));
		ball->addComponent<cogs::SphereCollider>(1.0f);
		ball->addComponent<cogs::RigidBody>(&physicsWorld, 1.0f);
		ball->getComponent<cogs::RigidBody>()->setActivationState(5);
		ball->getComponent<cogs::RigidBody>()->setLinearFactor(glm::vec3(1.0f, 1.0f, 0.0f));
		ball->getComponent<cogs::RigidBody>()->setRestitution(1.0f);
		ball->addComponent<BallBehavior>();

		for (int i = -30; i < 30; i += 4)
		{
				for (int j = -10; j < 0; j += 4)
				{
						cogs::Entity* brick = manager.create("Brick");
						brick->setTag("brick");
						brick->addComponent<cogs::MeshRenderer>(cogs::ResourceManager::getMesh("Models/TestModels/cube.obj"), &renderer3D);
						brick->transform()->translate(glm::vec3(0.0f + i, 30.0f + j, 0.0f));
						brick->addComponent<cogs::BoxCollider>(glm::vec3(1.0f, 1.0f, 1.0f));
						brick->addComponent<cogs::RigidBody>(&physicsWorld, 0.0f);
						brick->getComponent<cogs::RigidBody>()->setActivationState(5);
						brick->getComponent<cogs::RigidBody>()->setRestitution(1.0f);
				}
		}

		/*cogs::GLSLProgram* spriteShader = cogs::ResourceManager::getGLSLProgram("DefaultSprite", "Shaders/DefaultSprite.vs", "Shaders/DefaultSprite.fs");
		cogs::GLTexture2D* texture = cogs::ResourceManager::getGLTexture2D("Textures/img_test.png", "texture_diffuse");

		cogs::Material* spriteMaterial = cogs::ResourceManager::getMaterial("sprite_material");
		spriteMaterial->setDiffuseMap(texture);
		spriteMaterial->setShader(spriteShader);

		cogs::Sprite* testSprite = cogs::ResourceManager::getSprite("test_sprite", spriteMaterial, glm::vec2(400.0f, 400.0f), cogs::Color::white);

		cogs::Entity* spriteTest = manager.create("Sprite1");
		spriteTest->addComponent<cogs::SpriteRenderer>(testSprite, &renderer2D);
		spriteTest->addComponent<SpriteController>(500.0f);
		spriteTest->transform()->setWorldPosition(glm::vec3(0.0f, 0.0f, -10.0f));

		cogs::Entity* spriteTest2 = manager.create("Sprite2");
		spriteTest2->addComponent<cogs::SpriteRenderer>(testSprite, &renderer2D);
		spriteTest2->transform()->setParent(spriteTest->transform());
		spriteTest2->transform()->setLocalPosition(glm::vec3(400.0f, 400.0f, 0.0f));

		cogs::Entity* spriteTest3 = manager.create("Sprite3");
		spriteTest3->addComponent<cogs::SpriteRenderer>(testSprite, &renderer2D);
		spriteTest3->transform()->setParent(spriteTest2->transform());
		spriteTest3->transform()->setLocalPosition(glm::vec3(400.0f, 400.0f, 0.0f));

		cogs::BulletDebugRenderer debugRenderer;

		debugRenderer.setDebugMode(debugRenderer.DBG_DrawWireframe);
		physicsWorld.setDebugDrawer(&debugRenderer);

		while (!quit)
		{
				fpsLimiter.beginFrame();

				cogs::Input::update();

				//process input
				SDL_Event evnt;
				while (SDL_PollEvent(&evnt))
				{
						cogs::GUI::onSDLEvent(evnt);
						switch (evnt.type)
						{
								case SDL_QUIT:
								{
										quit = true;
										break;
								}
								case SDL_MOUSEMOTION:
								{
										cogs::Input::setMouseCoords(static_cast<float>(evnt.motion.x), static_cast<float>(evnt.motion.y));
										cogs::Input::setMouseMotion(static_cast<float>(evnt.motion.xrel), static_cast<float>(evnt.motion.yrel));
										break;
								}
								case SDL_KEYDOWN:
								{
										cogs::Input::pressKey(evnt.key.keysym.sym);
										break;
								}
								case SDL_KEYUP:
								{
										cogs::Input::releaseKey(evnt.key.keysym.sym);
										break;
								}
								case SDL_MOUSEBUTTONDOWN:
								{
										cogs::Input::pressKey(evnt.button.button);
										break;
								}
								case SDL_MOUSEBUTTONUP:
								{
										cogs::Input::releaseKey(evnt.button.button);
										break;
								}
								case SDL_MOUSEWHEEL:
								{
										break;
								}
								case SDL_WINDOWEVENT:
								{
										window.handleEvent(evnt);
								}
						}
				}
				if (cogs::Input::isKeyPressed(cogs::KeyCode::TAB))
				{
						debugMode = !debugMode;
				}
				manager.refresh();
				manager.update(fpsLimiter.deltaTime());

				physicsWorld.stepSimulation();
				cogs::GUI::update();

				for (cogs::Camera* camera : cogs::Camera::getAllCameras())
				{
						if (!camera->getEntity()->isActive())
						{
								continue;
						}
						// set the current camera
						cogs::Camera::setCurrent(camera);

						// set the render target
						cogs::Framebuffer::setActive(camera->getRenderTarget());

						// clear the window with the camera's background color
						window.setClearColor(camera->getBackgroundColor());
						window.clear(true, true);

						renderer2D.begin();
						renderer3D.begin();

						// call the render function of all entities (submits all entities with sprite and mesh renderers)
						manager.render();

						renderer2D.end();
						renderer3D.end();

						//render opaque objects
						renderer3D.flush();

						if (debugMode)
						{
								//use the debug renderer to draw the debug physics world
								physicsWorld.debugDrawWorld();
								debugRenderer.end();
								debugRenderer.render(camera->getViewMatrix(), camera->getProjectionMatrix(), 5.0f);
						}

						//render the camera's skybox if it has one
						camera->renderSkybox();

						//render transparent objects (sorter or blended)
						renderer2D.flush();

						//set the render target to the default window
						cogs::Framebuffer::setActive(nullptr);
				}
				cogs::GUI::render();

				window.swapBuffer();

				fpsLimiter.endFrame();

				static int counter = 0;

				static float fps = 0.0f;
				static float dt = 0.0f;

				fps += fpsLimiter.fps();
				dt += fpsLimiter.deltaTime();

				if (counter == 100)
				{
						fps /= 100.0f;
						dt /= 100.0f;
						window.setWindowTitle("FPS: " + std::to_string(fps) + " DT: " + std::to_string(dt));
						counter = 0;
				}
				else
				{
						counter++;
				}
		}
		manager.clear();
		cogs::GUI::destroy();
		cogs::ResourceManager::clear();
		window.close();*/

		cogs::Application app;

		app.addScene(std::make_unique<MainMenu>(&app));
		app.addScene(std::make_unique<TestScene>(&app));

		app.run("Test", 1024, 576);

		return 0;
}