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
				std::vector<std::unique_ptr<Scene>> m_scenes;
				Application* m_app{ nullptr };
				int m_currentSceneID{ -1 };
		};
}