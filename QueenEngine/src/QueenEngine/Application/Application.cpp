#include "Application.h"

namespace Queen
{
	namespace Application
	{

		Application::Application()
		{

		}

		Application::Application(const char* title, Window::uint&& width, Window::uint&& height)
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;
		}

		Application::~Application()
		{

		}

		void Application::Start()
		{
			Managers::LogManager::Get().Start();
			Managers::MemoryManager::Get().Start();
			Managers::WindowManager::Get().Start();
			Managers::EventManager::Get().Start();
			Managers::ImGUIManager::Get().Start();

			//Create Window Application
			if (!Queen::Managers::WindowManager::Get().CreateWWindow(m_Title, m_Width, m_Height))
				exit(-1);

			m_Window = Queen::Managers::WindowManager::Get().GetWWindow(m_Title);
			Managers::ImGUIManager::Get().Init(m_Window, "#version 410");
		}

		void Application::Shutdown()
		{
			Managers::ImGUIManager::Get().Shutdown();
			Managers::EventManager::Get().Shutdown();
			Managers::WindowManager::Get().Shutdown();
			Managers::MemoryManager::Get().Shutdown();
			Managers::LogManager::Get().Shutdown();
		}

		void Application::OnEvent()
		{
			bool draw = true;
			if (Queen::Managers::InputManager::Get().IsKeyDown(GLFW_KEY_W))
			{
				QE_LOG(QE_SUCCESS, "FORWARD");
				QE_GUI_LOG(QE_SUCCESS, GUI::Logger::Get(), "FORWARD");
			}
			else if (Queen::Managers::InputManager::Get().IsKeyDown(GLFW_KEY_A))
			{
				QE_LOG(QE_SUCCESS, "LEFT");
				QE_GUI_LOG(QE_SUCCESS, GUI::Logger::Get(), "LEFT");
			}
			else if (Queen::Managers::InputManager::Get().IsKeyDown(GLFW_KEY_S))
			{
				QE_LOG(QE_SUCCESS, "BACK");
				QE_GUI_LOG(QE_SUCCESS, GUI::Logger::Get(), "BACK");
			}
			else if (Queen::Managers::InputManager::Get().IsKeyDown(GLFW_KEY_D))
			{
				QE_LOG(QE_SUCCESS, "RIGHT");
				QE_GUI_LOG(QE_SUCCESS, GUI::Logger::Get(), "RIGHT");
			}

			if(Queen::Managers::InputManager::Get().IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
				QE_LOG(QE_SUCCESS, "LEFT CLICK");
			else if(Queen::Managers::InputManager::Get().IsMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
				QE_LOG(QE_SUCCESS, "RIGHT CLICK");
			else if(Queen::Managers::InputManager::Get().IsMouseButtonDown(GLFW_MOUSE_BUTTON_MIDDLE))
				QE_LOG(QE_SUCCESS, "WHEEL CLICK");
		}

		void Application::Run()
		{
			while (Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->isRunning())
			{
				Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Render();
				
				Queen::Managers::ImGUIManager::Get().OnRender();

				this->OnEvent();

				Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Update();
			}
		}
	}
}