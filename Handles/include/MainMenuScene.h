#pragma once

#include <Cogs\include\Scene.h>

class MainMenu : public cogs::Scene
{
public:
		MainMenu(cogs::Application* _app);
		~MainMenu();

		void OnEntry() override;
private:

};