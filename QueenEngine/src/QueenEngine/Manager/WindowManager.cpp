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
				if (!DestroyAllWWindows())
					QE_LOG(QE_ERROR, "Error!");
				else
					QE_LOG(QE_WARN, g_WIN_MAN_INFO_SHUTDOWN);
				m_Running = false;
			}
		}

		bool WindowManager::InitLibraries()
		{
			QE_LOG(QE_TRACE, g_INIT_WIN_GLFW);
			if (!glfwInit())
			{
				QE_LOG(QE_ERROR, g_ERROR_INIT_WIN_GLFW);
				return false;
			}
			QE_LOG(QE_TRACE, g_INIT_SUCCESS_WIN_GLFW);

			m_GlwfInitialised = true;
			return true;
		}

		bool WindowManager::CreateWWindow(const char* title, Window::uint& width, Window::uint& height)
		{
			if (!m_GlwfInitialised)
				InitLibraries();

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

				NotifyEvents(w->GetWindowHandler(), true);

				m_Windows[title] = w;
				QE_LOG(QE_SUCCESS, g_WIN_INIT_SUCCESS);
			}

			return true;
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

		void WindowManager::NotifyEvents(GLFWwindow* wind, bool debug)
		{
			if (debug)
			{
				//Resize
				glfwSetWindowSizeCallback(wind, Window_Resize_Callback);
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