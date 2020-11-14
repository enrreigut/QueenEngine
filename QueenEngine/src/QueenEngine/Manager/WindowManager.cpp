#include "WindowManager.h"

namespace Queen
{
	namespace Managers
	{
		//callbacks
		void Window_Resize_Callback(GLFWwindow* window, int width, int height);
		
		WindowManager::WindowManager()
		{

		}

		WindowManager::~WindowManager()
		{
			QE_LOG(QE_TRACE, g_WIN_MAN_INFO_DESTROYED);
		}

		void WindowManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;
				QE_LOG(QE_TRACE, g_WIN_MAN_INFO_START);

				InputManager::Get().Start();
			}
			else
			{
				QE_LOG(QE_ERROR, g_WIN_MAN_ERROR_ALREADY_STARTED);
			}
		}

		void WindowManager::Shutdown()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_WIN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				InputManager::Get().Shutdown();

				if (!DestroyAllWWindows())
					QE_LOG(QE_ERROR, "Error!");
				else
					QE_LOG(QE_WARN, g_WIN_MAN_INFO_SHUTDOWN);
				m_Running = false;
			}
		}

		bool WindowManager::InitGLFW()
		{
			if (!m_GlwfInitialised)
			{
				QE_LOG(QE_TRACE, g_INIT_WIN_GLFW);
				if (!glfwInit())
				{
					QE_LOG(QE_ERROR, g_ERROR_INIT_WIN_GLFW);
					return false;
				}
				QE_LOG(QE_SUCCESS, g_INIT_SUCCESS_WIN_GLFW);

				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

				m_GlwfInitialised = true;
			}
			return m_GlwfInitialised;
		}

		bool  WindowManager::InitGLEW()
		{
			if (!m_GlewInitialised)
			{
				QE_LOG(QE_TRACE, g_INIT_WIN_GLEW);
				GLenum err = glewInit();
				if (GLEW_OK != err)
				{
					QE_LOG(QE_ERROR, g_ERROR_INIT_WIN_GLEW);
					return false;
				}
				QE_LOG(QE_SUCCESS, g_INIT_SUCCESS_WIN_GLEW);

				m_GlewInitialised = true;
			}

			return m_GlewInitialised;
		}

		bool WindowManager::CreateWWindow(const char* title, Window::uint& width, Window::uint& height)
		{
			if (m_Running)
			{
				if (!m_GlwfInitialised)
				{
					if (!InitGLFW())
					{
						return false;
					}
				}

				if (m_Windows.find(title) != m_Windows.end())
				{
					QE_LOG_PARAMS(QE_ERROR, g_WIN_ERROR_DUPLICATE, title);
					return false;
				}
				else
				{
					Window::Window* w = new Window::Window;

					QE_LOG_PARAMS(QE_TRACE, g_WIN_INIT, title, width, height);

					if (!w->Init(title, width, height))
					{
						QE_LOG(QE_ERROR, g_WIN_ERROR_INIT);
						return false;
					}

					if (!m_GlewInitialised)
					{
						if (!InitGLEW())
						{
							return false;
						}
					}

					//Set To false if no debug is wanted!
					NotifyEvents(w->GetWindowHandler(), false);
					m_Windows[title] = w;
					
					glfwSwapInterval(1);

					QE_LOG(QE_SUCCESS, g_WIN_INIT_SUCCESS);
				}

				return true;
			}
			else
			{
				QE_LOG(QE_ERROR, g_WIN_MAN_ERROR_NOT_STARTED);
				return false;
			}
		}

		bool WindowManager::DestroyWWindow(const char* title)
		{
			if (m_Windows.find(title) == m_Windows.end())
			{
				QE_LOG_PARAMS(QE_ERROR, g_WIN_ERROR_NOT_EXIST, title);
				return false;
			}
			else
			{
				if (!m_Windows[title]->Shutdown())
				{
					QE_LOG(QE_ERROR, g_WIN_ERROR_UNEXPECTED);
					return false;
				}

				m_Windows[title]->Shutdown();
				delete m_Windows[title];

				return m_Windows.erase(title);
			}
		}

		bool WindowManager::DestroyAllWWindows()
		{
			std::vector<const char*> keys;
			for (auto it = m_Windows.begin(); it != m_Windows.end(); ++it)
				keys.push_back(it->first);

			for (auto elem : keys)
			{
				m_Windows[elem]->Shutdown();
				if (!m_Windows.erase(elem))
				{
					QE_LOG(QE_ERROR, g_WIN_ERROR_UNEXPECTED);
					return false;
				}
			}

			return true;
		}

		void WindowManager::SetTargetWindow(Window::Window* window)
		{
			if (window != nullptr)
			{
				m_TargetWindow = window;
			}
		}

		void WindowManager::SetWindowWidth(Window::Window& wnd, Window::uint& width) 
		{
			wnd.SetWidth(width);
		}
		
		void WindowManager::SetWindowHeight(Window::Window& wnd, Window::uint& width)
		{
			wnd.SetHeight(width);
		}

		void WindowManager::SetWindowWidth(const char* wndName, Window::uint& width)
		{
			m_Windows[wndName]->SetWidth(width);
		}

		void WindowManager::SetWindowHeight(const char* wndName, Window::uint& height)
		{
			m_Windows[wndName]->SetHeight(height);
		}

		void WindowManager::NotifyEvents(GLFWwindow* wind, bool debug)
		{
			InputManager::Get().p_DebugEvents = debug;

			if(!InputManager::Get().p_DebugEvents)
				QE_LOG(QE_INFO, "Ddebug mode is not enable. Events will not be outputed at console");
			
			{
				//Resize
				glfwSetWindowSizeCallback(wind, Window_Resize_Callback);

				//keyscan
				glfwSetKeyCallback(wind, InputManager::Get().Window_Keyscan_Callback);

				//Mouse Input
				glfwSetMouseButtonCallback(wind, InputManager::Get().Window_Mouse_Button_callback);
				glfwSetCursorPosCallback(wind, InputManager::Get().Window_Mouse_Position_Callback);
				glfwSetScrollCallback(wind, InputManager::Get().Window_Mouse_Scroll_Callback);
			}
		}

		//Resize Callback
		void Window_Resize_Callback(GLFWwindow* window, int width, int height)
		{
			Window::Window* wind = (Window::Window*)glfwGetWindowUserPointer(window);
			wind->SetWidth((Window::uint&)width);
			wind->SetHeight((Window::uint&)height);

			QE_LOG_PARAMS(QE_TRACE, g_WIN_CALLBACK_RESIZE, wind->GetWidth(), wind->GetHeight());
		}
	}
}