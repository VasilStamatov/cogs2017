#pragma once

#include <Cogs\include\Scene.h>

class TestScene : public cogs::Scene
{
public:
		TestScene(cogs::Application* _app);
		~TestScene();

		void OnEntry() override;
private:

};