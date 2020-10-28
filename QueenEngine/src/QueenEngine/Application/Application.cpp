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

			//Create ImGUI context
			const char* glsl_version = "#version 410";
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			ImGui::StyleColorsDark();

			ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindowHandler(), true);
			ImGui_ImplOpenGL3_Init(glsl_version);
		}

		void Application::Shutdown()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();

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
			else if(Queen::Managers::InputManager::Get().IsMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
				QE_LOG(QE_SUCCESS, "RIGHT CLICK");
			else if(Queen::Managers::InputManager::Get().IsMouseButtonDown(GLFW_MOUSE_BUTTON_MIDDLE))
				QE_LOG(QE_SUCCESS, "WHEEL CLICK");
		}

		void Application::Run()
		{
			bool show_demo_window = true;

			float vertex[] = {
					-0.5f, -0.5f, 0.0f,
					0.0f, 0.5f, 0.0f,
					0.5f, -0.5f, 0.0f
			};

			GLuint vbo = 0;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertex, GL_STATIC_DRAW);

			while (Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->isRunning())
			{
				Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Update();
				Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Render(vbo);

				/*ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();*/

				this->OnEvent();
			}
		}
	}
}