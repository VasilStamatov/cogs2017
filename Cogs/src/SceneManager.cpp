#include "../include/SceneManager.h"

#include "../include/Scene.h"

namespace cogs
{
		SceneManager::SceneManager(Application* _app) : m_app(_app)
		{
		}
		SceneManager::~SceneManager()
		{
				m_scenes.clear();
		}
		void SceneManager::loadScene(int _sceneID)
		{
				for (size_t i = 0; i < m_scenes.size(); i++)
				{
						if (m_scenes.at(i)->m_sceneID == _sceneID)
						{
								m_scenes.at(m_currentSceneID)->OnExit();
								m_currentSceneID = i;
								m_scenes.at(m_currentSceneID)->OnEntry();
								return;
						}
				}
		}
		void SceneManager::loadScene(const std::string & _sceneName)
		{
				for (size_t i = 0; i < m_scenes.size(); i++)
				{
						if (m_scenes.at(i)->m_sceneName == _sceneName)
						{
								m_scenes.at(m_currentSceneID)->OnExit();
								m_currentSceneID = i;
								m_scenes.at(m_currentSceneID)->OnEntry();
								return;
						}
				}
		}
		void SceneManager::addScene(std::unique_ptr<Scene> _newScene)
		{
				_newScene->m_sceneID = m_scenes.size();
				m_scenes.push_back(std::move(_newScene));
				if (m_currentSceneID < 0)
				{
						m_currentSceneID = 0;
				}
		}
		Scene * SceneManager::getCurrent()
		{
				if (m_currentSceneID < 0)
				{
						return nullptr;
				}
				return m_scenes.at(m_currentSceneID).get();
		}
}