#include "../include/Window.h"

#include <GL\glew.h>

#include "../include/GUI.h"

namespace cogs
{
		int Window::m_width{ 0 };
		int Window::m_height{ 0 };

		int Window::create(const std::string& _windowName, int _screenWidth,
				int _screenHeight, WindowFlag _windowFlags)
		{
				initSDL();

				Uint32 flags = SDL_WINDOW_OPENGL; //base needed flag
				m_title = _windowName;
				m_width = _screenWidth;
				m_height = _screenHeight;

				switch (_windowFlags)
				{
				case cogs::WindowFlag::NONE:
						break;
				case cogs::WindowFlag::INVISIBLE:
						flags |= SDL_WINDOW_HIDDEN;
						break;
				case cogs::WindowFlag::FULLSCREEN:
						flags |= SDL_WINDOW_FULLSCREEN;
						break;
				case cogs::WindowFlag::FULLSCREEN_DESKTOP:
						flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
						break;
				case cogs::WindowFlag::BORDERLESS:
						flags |= SDL_WINDOW_BORDERLESS;
						break;
				case cogs::WindowFlag::RESIZABLE:
						flags |= SDL_WINDOW_RESIZABLE;
						break;
				case cogs::WindowFlag::MINIMIZED:
						flags |= SDL_WINDOW_MINIMIZED;
						break;
				case cogs::WindowFlag::MAXIMIZED:
						flags |= SDL_WINDOW_MAXIMIZED;
						break;
				case cogs::WindowFlag::INPUT_GRABBED:
						flags |= SDL_WINDOW_INPUT_GRABBED;
						break;
				default:
						break;
				}

				//Create an SDL window
				m_sdlWindow = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, flags);

				if (m_sdlWindow == nullptr)
				{
						throw std::runtime_error("Window could not be created");
				}

				m_mouseFocus = true;
				m_keyboardFocus = true;

				initGL();

				return 0; //Success!
		}

		void Window::close()
		{
				SDL_GL_DeleteContext(m_glContext);
				SDL_DestroyWindow(m_sdlWindow);
				SDL_Quit();

				m_sdlWindow = nullptr;
		}

		void Window::handleEvent(SDL_Event& _event)
		{
				switch (_event.window.event)
				{
				case SDL_WINDOWEVENT_SHOWN:
				{
						//window is shown
						break;
				}
				case SDL_WINDOWEVENT_HIDDEN:
				{
						//window is hidden
						break;
				}
				case SDL_WINDOWEVENT_EXPOSED:
				{
						//the window is visible again, make it render !
						break;
				}
				case SDL_WINDOWEVENT_MOVED:
				{
						//window has been moved
						break;
				}
				case SDL_WINDOWEVENT_RESIZED:
				{
						//window has been resized
						m_width = _event.window.data1;
						m_height = _event.window.data2;
						//glViewport(0, 0, m_width, m_height);
						GUI::notifyWindowResize(m_width, m_height);
						break;
				}
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				{
						//window's size has changed
						m_width = _event.window.data1;
						m_height = _event.window.data2;
						//glViewport(0, 0, m_width, m_height);
						GUI::notifyWindowResize(m_width, m_height);
						break;
				}
				case SDL_WINDOWEVENT_MINIMIZED:
				{
						//window was minimized
						m_minimized = true;
						break;
				}
				case SDL_WINDOWEVENT_MAXIMIZED:
				{
						//window was maximized
						m_minimized = false;
						break;
				}
				case SDL_WINDOWEVENT_RESTORED:
				{
						//window has been restored
						m_minimized = false;
						break;
				}
				case SDL_WINDOWEVENT_ENTER:
				{
						//mouse entered the window
						m_mouseFocus = true;
						break;
				}
				case SDL_WINDOWEVENT_LEAVE:
				{
						//mouse left the window
						m_mouseFocus = false;
						break;
				}
				case SDL_WINDOWEVENT_FOCUS_GAINED:
				{
						//window gained keyboard access/focus
						m_keyboardFocus = true;
						break;
				}
				case SDL_WINDOWEVENT_FOCUS_LOST:
				{
						//window lost keyboard access/focus
						m_keyboardFocus = false;
						break;
				}
				case SDL_WINDOWEVENT_CLOSE:
				{
						//window has been closed
						break;
				}
#if SDL_VERSION_ATLEAST(2, 0, 5)
				case SDL_WINDOWEVENT_TAKE_FOCUS:
				{
						//window has been offered a focus
						std::cout << "SDL_WINDOWEVENT_TAKE_FOCUS" << std::endl;
						break;
				}
				case SDL_WINDOWEVENT_HIT_TEST:
				{
						//window has a special hit test
						std::cout << "SDL_WINDOWEVENT_HIT_TEST" << std::endl;
						break;
				}
#endif
				default:
				{
						//IMPOSSIBLE!
						break;
				}
				}
		}

		void Window::swapBuffer()
		{
				SDL_GL_SwapWindow(m_sdlWindow);
		}

		void Window::clear(bool _color, bool _depth, bool _stencil /* = false */)
		{
				GLbitfield mask = 0;
				if (_color)
				{
						mask = GL_COLOR_BUFFER_BIT;
				}
				if (_depth)
				{
						mask |= GL_DEPTH_BUFFER_BIT;
				}
				if (_stencil)
				{
						mask |= GL_STENCIL_BUFFER_BIT;
				}
				glClear(mask);
		}

		void Window::refreshViewport()
		{
				glViewport(0, 0, m_width, m_height);
		}

		void Window::setFullscreen(bool _isFullscreen)
		{
				if (_isFullscreen)
				{
						SDL_SetWindowFullscreen(m_sdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
				}
				SDL_GetWindowSize(m_sdlWindow, &m_width, &m_height);
				GUI::notifyWindowResize(m_width, m_height);
		}

		void Window::setBorder(bool _hasBorders)
		{
				if (_hasBorders)
				{
						SDL_SetWindowBordered(m_sdlWindow, SDL_TRUE);
				}
				else
				{
						SDL_SetWindowBordered(m_sdlWindow, SDL_FALSE);
				}
		}

		void Window::setWindowTitle(const std::string & _title)
		{
				m_title = _title;
				SDL_SetWindowTitle(m_sdlWindow, _title.c_str());
		}

		void Window::setClearColor(const Color& _color)
		{
				glClearColor(_color.r / 255.0f, _color.g / 255.0f, _color.b / 255.0f, _color.a / 255.0f);
		}

		void Window::setRelativeMouseMode(int _enabled)
		{
				SDL_SetRelativeMouseMode(SDL_bool(_enabled));
		}

		void Window::showMouseCursor(bool _visible)
		{
				SDL_ShowCursor(_visible ? 1 : 0);
		}

		void Window::initSDL()
		{
				//initialize SDL
				SDL_Init(SDL_INIT_EVERYTHING);
				//The color bits
				SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
				SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
				SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
				SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
				//Tell SDL that we want a double buffered window so we dont get any flickering
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
				//set the depth size to 24 (default 16)
				SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
				//set the stencil size to 8 (default 0)
				SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
				//Enable multisampling
				SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
				SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

				// Use OpenGL core profile
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

				//set the accelerated visuals (it's possible that it's set by default but doing this just in case)
				SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		}

		void Window::initGL()
		{
				//Set up our OpenGL context
				m_glContext = SDL_GL_CreateContext(m_sdlWindow);

				if (m_glContext == nullptr)
				{
						throw std::runtime_error("GL context could not be created");
				}

				//Set up glew
				GLenum error = glewInit();
				if (error != GLEW_OK)
				{
						throw std::runtime_error("Glew could not be initialized");
				}

				//Set the background color to black
				glClearColor(0.0f, 0.0f, 0.0f, 1.0);

				//set vsync
				SDL_GL_SetSwapInterval(0);

				//Enable alpha blending
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

				//Enable face culling
				glEnable(GL_CULL_FACE);
				glFrontFace(GL_CCW);
				glCullFace(GL_BACK);

				//Enable depth testing
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LESS);

				//Enable multisampling
				//glEnable(GL_MULTISAMPLE);

				//Enable gamma correction
				//glEnable(GL_FRAMEBUFFER_SRGB);

				//Enable stencil testing
				//glEnable(GL_STENCIL_TEST);
				//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
				//glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
				//glStencilOpSeparate(GL_BACK, GL_KEEP, GL_KEEP, GL_REPLACE);
				//glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_KEEP);

				//Enable depth clamping
				//glEnable(GL_DEPTH_CLAMP);
		}
}