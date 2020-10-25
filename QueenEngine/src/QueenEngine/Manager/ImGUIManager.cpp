#include "ImGUIManager.h"

namespace Queen
{
	namespace Managers
	{

		ImGUIManager::ImGUIManager()
		{

		}
		
		ImGUIManager::~ImGUIManager()
		{
			QE_LOG(QE_TRACE, g_IMGUI_MAN_INFO_DESTROYED);
		}

		void ImGUIManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;

				QE_LOG(QE_TRACE, g_IMGUI_MAN_INFO_START);
			}
			else
			{
				QE_LOG(QE_ERROR, g_IMGUI_MAN_ERROR_ALREADY_STARTED);
			}
		}

		void ImGUIManager::Shutdown()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_IMGUI_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				ImGui_ImplOpenGL3_Shutdown();
				ImGui_ImplGlfw_Shutdown();
				ImGui::DestroyContext();

				QE_LOG(QE_WARN, g_IMGUI_MAN_INFO_SHUTDOWN);

				m_Running = false;
			}
		}

		void ImGUIManager::CreateContext()
		{
			//Create ImGUI context
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
		}

		void ImGUIManager::Init(Window::Window* wind, const char* glsl_version)
		{
			CreateContext();

			//Set Style
			ImGui::StyleColorsDark();

			ImGui_ImplGlfw_InitForOpenGL(wind->GetWindowHandler(), true);
			ImGui_ImplOpenGL3_Init(glsl_version);
		}

		void ImGUIManager::OnRender()
		{
			//Start Frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			//Create Demo Window
			ImGui::ShowDemoWindow(&show_demo_window);

			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			}

			//Render
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
	}
}