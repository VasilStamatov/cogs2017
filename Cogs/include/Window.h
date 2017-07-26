#pragma once

#include <string>
#include "../../dependencies/include/SDL/SDL.h"

#include "Color.h"

namespace cogs
{
		enum class WindowFlag : unsigned char
		{
				NONE,
				INVISIBLE,
				FULLSCREEN,
				FULLSCREEN_DESKTOP,
				BORDERLESS,
				RESIZABLE,
				MINIMIZED,
				MAXIMIZED,
				INPUT_GRABBED
		};

		class Window
		{
		public:
				Window() {}
				~Window() {}

				int create(const std::string& _windowName,
						int _screenWidth,
						int _screenHeight,
						WindowFlag _windowFlags);

				void close();

				void handleEvent(SDL_Event& _event);

				void swapBuffer();

				void clear(bool _color, bool _depth, bool _stencil = false);

				void refreshViewport();

				void setFullscreen(bool _isFullscreen);
				void setBorder(bool _hasBorders);
				void setWindowTitle(const std::string& _title);
				void setClearColor(const Color& _color);
				void setRelativeMouseMode(int _enabled);
				void showMouseCursor(bool _visible);

				inline const std::string& getTitle()    const noexcept { return m_title; }
				inline bool hasMouseFocus()													const noexcept { return m_mouseFocus; }
				inline bool hasKeyboardFocus()										const noexcept { return m_keyboardFocus; }
				inline bool isMinimized()															const noexcept { return m_minimized; }

				inline static int			getWidth()		noexcept { return m_width; }
				inline static int			getHeight()	noexcept { return m_height; }
				inline static float getAspect() noexcept { return (float)m_width / (float)m_height; }

		private:
				//SDL must be initialized before window creation
				void initSDL();
				//OGL context must be initialized after window creation
				void initGL();

		private:
				std::string m_title{ "default" };

				SDL_Window* m_sdlWindow{ nullptr };
				SDL_GLContext m_glContext;

				static int m_width;
				static int m_height;

				bool m_mouseFocus{ false };
				bool m_keyboardFocus{ false };
				bool m_fullscreen{ false };
				bool m_minimized{ false };
		};
}