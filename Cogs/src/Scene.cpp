#include "../include/Scene.h"
#include "../include/Application.h"

namespace cogs
{
		Scene::Scene(Application* _app) : m_app(_app)
		{
		}
		Scene::~Scene()
		{
				m_app = nullptr;
		}
		void Scene::OnExit()
		{
				m_app->m_entityManager.onLevelExit();
		}
		void Scene::setName(const std::string & _name)
		{
				m_sceneName = _name;
		}
		unsigned int Scene::getID() const noexcept
		{
				return m_sceneID;
		}
		const std::string & Scene::getName() const noexcept
		{
				return m_sceneName;
		}
		Entity * Scene::createEntity(const std::string & _name)
		{
				return m_app->m_entityManager.create(_name);
		}
		Physics * Scene::getPhysicsWorld()
		{
				return &m_app->m_physics;
		}
		Renderer2D * Scene::getRenderer2D()
		{
				return &m_app->m_renderer2D;
		}
		Renderer3D * Scene::getRenderer3D()
		{
				return &m_app->m_renderer3D;
		}
		ParticleRenderer * Scene::getParticleRenderer()
		{
				return &m_app->m_particleRenderer;
		}
		SceneManager * Scene::getSceneManager()
		{
				return &m_app->m_sceneManager;
		}
		ResourceManager * Scene::getResourceManager()
		{
				return &m_app->m_resourceManager;
		}
		void Scene::exitApplication()
		{
				m_app->m_running = false;
		}
}