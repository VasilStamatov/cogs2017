#pragma once

#include "../include/SceneManager.h"
#include "../include/Window.h"
#include "../include/Timing.h"
#include "../include/EntityManager.h"
#include "../include/Renderer2D.h"
#include "../include/Renderer3D.h"
#include "../include/ParticleRenderer.h"
#include "../include/Physics.h"
#include "../include/BulletDebugRenderer.h"

#define DEBUG_TEST 0

namespace cogs
{
		class Application
		{
				friend class Scene;
		public:
				Application();
				~Application();

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
				bool m_running{ false };

				Window m_window{};
				FpsLimiter m_fpsLimiter{ 1000.0f };
				SceneManager m_sceneManager{ this };
				EntityManager m_entityManager{};
				Renderer2D m_renderer2D{};
				Renderer3D m_renderer3D{};
				ParticleRenderer m_particleRenderer{};
				Physics m_physics{ 0.0f, -9.81f, 0.0f };
#if DEBUG_TEST
				BulletDebugRenderer m_debugRenderer{};
#endif
		};
}