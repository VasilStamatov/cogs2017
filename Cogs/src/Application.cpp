#include "../include/Application.h"

#include "../include/Input.h"
#include "../include/GUI.h"
#include "../include/ResourceManager.h"
#include "../include/Scene.h"
#include "../include/Camera.h"
#include "../include/Framebuffer.h"

namespace cogs
{
		Application::Application()
		{
		}

		Application::~Application()
		{
		}

		void Application::run(const std::string & _windowName, int _windowWidth, int _windowHeight)
		{
				m_running = true;
				//initialize SDL and OpenGL and create the window
				m_window.create(_windowName, _windowWidth, _windowHeight, WindowCreationFlags::RESIZABLE);

				//initialize opengl renderers if needed
				m_renderer2D.init();
				m_particleRenderer.init();

				//initialize gui systems
				cogs::GUI::init("GUI");
				cogs::GUI::loadScheme("TaharezLook.scheme");
				cogs::GUI::setFont("DejaVuSans-10");
				cogs::GUI::setMouseCursor("TaharezLook/MouseArrow");
				cogs::GUI::hideMouseCursor();

				//m_window.showMouseCursor(false);

#if DEBUG_TEST
				m_debugRenderer.init();
				m_debugRenderer.setDebugMode(m_debugRenderer.DBG_DrawWireframe);
				m_physics.setDebugDrawer(&m_debugRenderer);
#endif

				//load the first scene
				m_sceneManager.loadScene(0);

				//begin game loop
				loop();

				//exit app
				shutdown();
		}

		void Application::addScene(std::unique_ptr<Scene> _newScene)
		{
				m_sceneManager.addScene(std::move(_newScene));
		}

		void Application::loop()
		{
				while (m_running)
				{
						m_fpsLimiter.beginFrame();

						Input::update();

						handleEvents();

						update(m_fpsLimiter.deltaTime());

						if (m_running && !m_window.isMinimized())
						{
								m_window.refreshViewport();
								render();
								m_window.swapBuffer();
						}
						m_fpsLimiter.endFrame();

						static int counter = 0;

						static float fps = 0.0f;
						static float dt = 0.0f;

						fps += m_fpsLimiter.fps();
						dt += m_fpsLimiter.deltaTime();

						if (counter == 100)
						{
								fps /= 100.0f;
								dt /= 100.0f;
								m_window.setWindowTitle("FPS: " + std::to_string(fps) + " DT: " + std::to_string(dt));
								counter = 0;
						}
						else
						{
								counter++;
						}

				}
		}

		void Application::update(float _deltaTime)
		{
				m_entityManager.update(_deltaTime);
				m_entityManager.refresh();
				m_physics.stepSimulation();
				GUI::update();
		}

		void Application::handleEvents()
		{
				SDL_Event evnt;
				while (SDL_PollEvent(&evnt))
				{
						GUI::onSDLEvent(evnt);
						switch (evnt.type)
						{
								case SDL_QUIT:
								{
										m_running = false;
										break;
								}
								case SDL_MOUSEMOTION:
								{
										Input::setMouseCoords(static_cast<float>(evnt.motion.x), static_cast<float>(evnt.motion.y));
										Input::setMouseMotion(static_cast<float>(evnt.motion.xrel), static_cast<float>(evnt.motion.yrel));
										break;
								}
								case SDL_KEYDOWN:
								{
										Input::pressKey(evnt.key.keysym.sym);
										break;
								}
								case SDL_KEYUP:
								{
										Input::releaseKey(evnt.key.keysym.sym);
										break;
								}
								case SDL_MOUSEBUTTONDOWN:
								{
										Input::pressKey(evnt.button.button);
										break;
								}
								case SDL_MOUSEBUTTONUP:
								{
										Input::releaseKey(evnt.button.button);
										break;
								}
								case SDL_MOUSEWHEEL:
								{
										break;
								}
								case SDL_WINDOWEVENT:
								{
										m_window.handleEvent(evnt);
								}
						}
				}
		}

		void Application::render()
		{
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
						m_window.setClearColor(camera->getBackgroundColor());
						m_window.clear(true, true);

						m_renderer2D.begin();
						m_renderer3D.begin();
						m_particleRenderer.begin();

						// call the render function of all entities (submits all entities with sprite and mesh renderers)
						m_entityManager.render();

						m_renderer2D.end();
						m_renderer3D.end();
						m_particleRenderer.end();

						//render opaque objects
						m_renderer3D.flush();

#if DEBUG_TEST
						//use the debug renderer to draw the debug physics world
						m_physics.debugDrawWorld();
						m_debugRenderer.end();
						m_debugRenderer.render(camera->getViewMatrix(), camera->getProjectionMatrix(), 3.0f);
#endif

						//render the camera's skybox if it has one
						camera->renderSkybox();

						//render transparent objects (sorter or blended)
						m_renderer2D.flush();
						m_particleRenderer.flush();

						//set the render target to the default window
						cogs::Framebuffer::setActive(nullptr);
				}
				cogs::GUI::render();
		}

		void Application::shutdown()
		{
				m_entityManager.clear();
				GUI::destroy();
				ResourceManager::clear();
				m_window.close();
		}

		void Application::setDesiredFPS(float _fps)
		{
				m_fpsLimiter.setMaxFPS(_fps);
		}
}