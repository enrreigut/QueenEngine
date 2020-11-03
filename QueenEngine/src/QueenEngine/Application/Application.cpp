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

			//===RENDER START==

			//Render First Scene in Queue
			if (m_Scenes.size() > 0)
			{
				m_CurrentScene = m_Scenes.begin()->second;
				m_CurrentScene->Load();
			}

			//=================
			m_LastTime = glfwGetTime();
		}

		void Application::Shutdown()
		{
			Managers::ImGUIManager::Get().Shutdown(); 
			Managers::RendererManager::Get().Shutdown();
			Managers::EventManager::Get().Shutdown();
			Managers::WindowManager::Get().Shutdown();
			Managers::MemoryManager::Get().Shutdown();
			Managers::LogManager::Get().Shutdown();
		}

		void Application::LoadScene(Scenes::Scene& scene)
		{
			if (m_Scenes.find(scene.GetSceneName()) == m_Scenes.end())
			{
				m_Scenes[scene.GetSceneName()] = &scene;
			}
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
				Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Render();

				//Prototipe
				//We have a scene
				//Scene has all enetities
				//for auto* ent: Scene.GeEntities()
				//	ent->Draw();

				//Process to draw an Entity
				
				//Managers::RendererManager::Get().UseProgram();

				if (xOffset <= -1.0f)
					increment += 0.1f;
				else if(xOffset >= 1.0f)
					increment = -0.1f;

				xOffset += increment * 0.125f;

				if (m_CurrentScene != nullptr)
				{
					m_CurrentScene->RenderScene();
				}

				//Stop Here
				
				Queen::Managers::ImGUIManager::Get().OnRender();
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
				QE_LOG_PARAMS(QE_SUCCESS, "FPS: {v}, {v} ms per frame", m_Frames, 1000.0 / double(m_Frames));

				m_Frames = 0;
				m_LastTime += 1.0;
			}
		}
	}
}