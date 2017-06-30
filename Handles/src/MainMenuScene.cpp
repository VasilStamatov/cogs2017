#include "../include/MainMenuScene.h"

#include <Cogs\include\Application.h>
#include <Cogs\include\Button.h>
#include <Cogs\include\Camera.h>
#include <Cogs\include\Window.h>

MainMenu::MainMenu(cogs::Application* _app) : Scene(_app)
{
		setName("TestScene");
}

MainMenu::~MainMenu()
{
}

void MainMenu::OnEntry()
{
		cogs::Entity* mainCamera = createEntity("MainCamera");
		mainCamera->transform()->translate(glm::vec3(0.0f, 0.0f, 55.0f));
		cogs::Camera* cam = mainCamera->addComponent<cogs::Camera>();
		cam->setProjectionType(false);

		cogs::Entity* playButton = createEntity("Play");
		playButton->addComponent<cogs::Button>("Play Game", glm::vec4(0.5f, 0.5f, 0.0f, 0.0f), glm::vec4(-50.0f, 0.0f, 100.0f, 50.0f));
		playButton->getComponent<cogs::Button>()->addEvent([this](const CEGUI::EventArgs&)
		{
				getSceneManager()->loadScene(getID()+1);
				return true; 
		});

		cogs::Entity* exitButton = createEntity("Exit");
		exitButton->addComponent<cogs::Button>("Exit Game", glm::vec4(0.5f, 0.5f, 0.0f, 0.0f), glm::vec4(-50.0f, 50.0f, 100.0f, 50.0f));
		exitButton->getComponent<cogs::Button>()->addEvent([this](const CEGUI::EventArgs&) 
		{
				exitApplication(); 
				return true; 
		});
}