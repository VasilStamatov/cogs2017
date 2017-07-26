#pragma once

#define DEBUG_TEST 0

#include "../include/SceneManager.h"
#include "../include/Window.h"
#include "../include/Timing.h"
#include "../include/EntityManager.h"
#include "../include/Renderer2D.h"
#include "../include/Renderer3D.h"
#include "../include/ParticleRenderer.h"
#include "../include/Physics.h"
#include "../include/ResourceManager.h"

#if DEBUG_TEST
#include "../include/BulletDebugRenderer.h"
#endif

namespace cogs
{
		class Application final
		{
				friend class Scene;
		public:
				Application();
				~Application();

				Application(const Application& _other) = delete;
				Application& operator=(const Application& _rhs) = delete;

				void run(const std::string& _windowName, int _windowWidth, int _windowHeight);

				void addScene(std::unique_ptr<Scene> _newScene);

		private:
				void loop();
				void update(float _deltaTime);
				void handleEvents();
				void render();
				void shutdown();
				void setDesiredFPS(float _fps);

		private:
				Window m_window{}; //40
				FpsLimiter m_fpsLimiter{ 1000.0f };	//40
				SceneManager m_sceneManager{ this };	//24
				EntityManager m_entityManager{};	//16
				Renderer2D m_renderer2D{};	//68
				Renderer3D m_renderer3D{};	//44
				Physics m_physics{ 0.0f, -9.81f, 0.0f };	//48
				ResourceManager m_resourceManager;	//16
				ParticleRenderer m_particleRenderer{ m_resourceManager };	//68
																																																																								
#if DEBUG_TEST																																																										
				BulletDebugRenderer m_debugRenderer{}; //60
#endif

				bool m_running{ false }; // 1
		};
}