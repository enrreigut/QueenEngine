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

		void Application::InitEngine()
		{
			Managers::LogManager::Get().Start();
			Managers::MemoryManager::Get().Start();
			Managers::WindowManager::Get().Start();
			Managers::EventManager::Get().Start();
			Managers::RendererManager::Get().Start();
			Managers::ImGUIManager::Get().Start();
			Managers::SceneManager::Get().Start();

			//Create Window Application
			if (!Queen::Managers::WindowManager::Get().CreateWWindow(m_Title, m_Width, m_Height))
				exit(-1);

			//Init ImGUI
			m_Window = Queen::Managers::WindowManager::Get().GetWWindow(m_Title);
			Managers::ImGUIManager::Get().Init(m_Window, "#version 410");

			//Set 1 to Limit FPS to 60
			glfwSwapInterval(1);
		}

		void Application::Start()
		{
			//Set to render the Scene with the Defult Flag
			Queen::Managers::RendererManager::Get().SetRenderScene();

			//Create Frame Buffer			
			Queen::Managers::RendererManager::Get().CreateFrameBuffer(1080.0f, 720.0f);

			m_LastTime = glfwGetTime();
		}

		void Application::Shutdown()
		{
			Managers::SceneManager::Get().Shutdown();
			Managers::ImGUIManager::Get().Shutdown(); 
			Managers::RendererManager::Get().Shutdown();
			Managers::EventManager::Get().Shutdown();
			Managers::WindowManager::Get().Shutdown();
			Managers::MemoryManager::Get().Shutdown();
			Managers::LogManager::Get().Shutdown();
		}

		void Application::LoadScene(Scenes::Scene& scene)
		{
			Managers::SceneManager::Get().AddScene(&scene);
		}

		void Application::OnEvent()
		{
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
				if (!m_Debug)
				{
					Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Render(m_Debug);

					Queen::Managers::RendererManager::Get().RenderScene((float)Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->GetWidth(), (float)Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->GetHeight());
				}
				else
				{
					//Start Rendering in FrameBuffer				
					Queen::Managers::RendererManager::Get().BindFrameBuffer();

					Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Render(m_Debug);
				
					//Render Scene
					Queen::Managers::RendererManager::Get().RenderScene((float)Queen::Managers::ImGUIManager::Get().GetViewportSize().x, (float)Queen::Managers::ImGUIManager::Get().GetViewportSize().y);

					//Stop Rendering in Frame Buffer				
					Queen::Managers::RendererManager::Get().UnbindFrameBuffer();
				
					//Render UI				
					Queen::Managers::RendererManager::Get().RenderImGUI();
				}
				
				this->OnEvent();
				
				Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Update();
				
				CalculateFPS();
			}
		}

		void Application::CalculateFPS()
		{
			double currentTime = glfwGetTime();
			m_Frames++;
			if (currentTime - m_LastTime >= 1.0) {
				// printf and reset
				QE_GUI_LOG_PARAMS(QE_SUCCESS, GUI::Logger::Get(), "FPS: {v}, {v} ms per frame", m_Frames, 1000.0 / double(m_Frames));

				m_Frames = 0;
				m_LastTime += 1.0;
			}
		}
	}
}