#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <SDL/SDL_events.h>
#include <glm/vec4.hpp>

#include "Timing.h"

namespace cogs
{
		class GUI
		{
		public:
				//initialize the gui
				static void init(const std::string& _resourceDirectory);
				//destroy the gui
				static void destroy();
				//draw the gui
				static void render();
				//update the gui
				static void update();
				//sets the mouse cursor to a custom image
				static void setMouseCursor(const std::string& _imageFile);
				//shows teh mouse cursor
				static void showMouseCursor();
				//hides the mouse cursor
				static void hideMouseCursor();
				//handles SDL events
				static void onSDLEvent(SDL_Event& _evnt);
				//Loads a scheme file
				static void loadScheme(const std::string& _schemeFile);
				//Sets the font the gui uses
				static void setFont(const std::string& _fontFile);
				//create a widget destrect perc
				static CEGUI::Window* createWidget(const std::string& _type, const glm::vec4& _destRectPerc, const glm::vec4& _destRectPix, const std::string& _name = "");
				//create a child widget (has a parent)
				static CEGUI::Window* createWidget(CEGUI::Window* _parent, const std::string& _type, const glm::vec4& _destRectPerc, const glm::vec4& _destRectPix, const std::string& _name = "");
				//sets the widget destination rectangle
				static void setWidgetDestRect(CEGUI::Window* _widget, const glm::vec4& _destRectPerc, const glm::vec4& _destRectPix);
				//Destroy the widget
				static void destroyWidget(CEGUI::Window* _widget);
				//function to be called whenever the window is resized
				static void notifyWindowResize(float _screenWidth, float _screenHeight);

				static CEGUI::OpenGL3Renderer* getRenderer() noexcept { return m_renderer; }
				static const CEGUI::GUIContext* getContext() noexcept { return m_context; }
				static const std::string& getSchemeName()			 noexcept { return m_schemeName; }
				static bool isFreed()																							 noexcept { return m_freed; }

		private:
				GUI();
				~GUI();

				static CEGUI::Key::Scan SDLKeyToCEGUIKey(SDL_Keycode _key);
				static CEGUI::MouseButton SDLButtonToCEGUIButton(Uint8 _sdlButton);

		private:
				static std::string m_schemeName;
				static HRTimer m_timer;
				static CEGUI::OpenGL3Renderer* m_renderer;
				static CEGUI::GUIContext* m_context;
				static CEGUI::Window* m_root;
				static bool m_freed;
		};
}