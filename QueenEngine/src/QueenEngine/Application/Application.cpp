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

			//Create Window Application
			Queen::Managers::WindowManager::Get().CreateWWindow(m_Title, m_Width, m_Height);
			m_Window = Queen::Managers::WindowManager::Get().GetWWindow(m_Title);
		}

		void Application::Shutdown()
		{
			Managers::EventManager::Get().Shutdown();
			Managers::WindowManager::Get().Shutdown();
			Managers::MemoryManager::Get().Shutdown();
			Managers::LogManager::Get().Shutdown();
		}

		void Application::OnEvent()
		{
			if (Queen::Managers::InputManager::Get().IsKeyDown(GLFW_KEY_W))
				QE_LOG(QE_SUCCESS, "FORWARD");
			else if (Queen::Managers::InputManager::Get().IsKeyDown(GLFW_KEY_A))
				QE_LOG(QE_SUCCESS, "LEFT");
			else if (Queen::Managers::InputManager::Get().IsKeyDown(GLFW_KEY_S))
				QE_LOG(QE_SUCCESS, "BACK");
			else if (Queen::Managers::InputManager::Get().IsKeyDown(GLFW_KEY_D))
				QE_LOG(QE_SUCCESS, "RIGHT");

			if(Queen::Managers::InputManager::Get().IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
				QE_LOG(QE_SUCCESS, "LEFT CLICK");
		}

		void Application::Run()
		{
			while (Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->isRunning())
			{
				Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Render();
				Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Update();

				this->OnEvent();
			}
		}
	}
}