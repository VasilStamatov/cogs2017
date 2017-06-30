#pragma once

#include <vector>
#include <memory>

namespace cogs
{
		class Application;
		class Scene;

		class SceneManager
		{
		public:
				SceneManager(Application* _app);
				~SceneManager();

				void loadScene(int _sceneID);
				void loadScene(const std::string& _sceneName);
				void addScene(std::unique_ptr<Scene> _newScene);

				Scene* getCurrent();

		private:
				Application* m_app{ nullptr };
				std::vector<std::unique_ptr<Scene>> m_scenes;
				int m_currentSceneID{ -1 };
		};
}