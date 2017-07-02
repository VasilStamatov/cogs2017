#pragma once

#include <string>

namespace cogs
{
		class Application;
		class SceneManager;
		class Entity;
		class Physics;
		class Renderer2D;
		class Renderer3D;
		class ParticleRenderer;
		class ResourceManager;

		class Scene
		{
				friend class SceneManager;
		public:
				Scene(Application* _app);
			 virtual ~Scene();

				virtual void OnEntry() = 0;
				virtual void OnExit();

				void setName(const std::string& _name);

				unsigned int getID()								 const noexcept;
				const std::string& getName() const noexcept;

		protected:
				Entity* createEntity(const std::string& _name);
				Physics* getPhysicsWorld();
				Renderer2D* getRenderer2D();
				Renderer3D* getRenderer3D();
				ParticleRenderer* getParticleRenderer();
				SceneManager* getSceneManager();
				ResourceManager* getResourceManager();

				void	exitApplication();
		private:
				Application* m_app{ nullptr };
				std::string m_sceneName{ "DefaultSceneName" };
				unsigned int m_sceneID{ 0 };
		};
}
