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

		void ImGUIManager::AddContext()
		{
			//Create ImGUI context
			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			
			m_io = io;
		}

		void ImGUIManager::Init(Window::Window* wind, const char* glsl_version)
		{
			
			AddContext();

			//Set Style
			ImGui::StyleColorsDark();

			ImGui_ImplGlfw_InitForOpenGL(wind->GetWindowHandler(), true);
			ImGui_ImplOpenGL3_Init(glsl_version);
		}

		bool ImGUIManager::CreateDockspace(bool* p_open)
		{
			static bool opt_fullscreen = true;
			static bool opt_padding = false;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->GetWorkPos());
				ImGui::SetNextWindowSize(viewport->GetWorkSize());
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}
			else
			{
				dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
			}

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
			// and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
			if (!opt_padding)
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", p_open, window_flags);
			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			if (m_io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}
			else
			{
				ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
				ImGui::Text("Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, or ");
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::SmallButton("click here"))
					m_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Options"))
				{
					// Disabling fullscreen would allow the window to be moved to the front of other windows,
					// which we can't undo at the moment without finer window depth/z control.
					ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
					ImGui::MenuItem("Padding", NULL, &opt_padding);
					ImGui::Separator();

					if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
					if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
					if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
					if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
					if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
					ImGui::Separator();

					if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
						*p_open = false;
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			ImGui::End();
			
			return true;
		}

		bool ImGUIManager::CreateLog(bool* p_open)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);			
			ImGui::Begin("QueenLog", p_open);					
			ImGui::End();

			GUI::Logger::Get().Draw("QueenLog", &showLog);

			return true;
		}

		bool ImGUIManager::CreateConsole(bool* p_open)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
			ImGui::Begin("QueenConsole", p_open);
			ImGui::End();

			return true;
		}
		
		bool ImGUIManager::CreateWindowWithImage(bool* p_open)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
			ImGui::Begin("Viewport", p_open);
			
			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
					
			if (m_ViewportSize != *((glm::vec2*)& ImGui::GetContentRegionAvail()))
			{
				m_FBO->Resize(m_ViewportSize);
				m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			}

			ImGui::Image((void*)m_FBO->GetFBO(), viewportPanelSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			ImGui::End();
			ImGui::PopStyleVar();
			return true;
		}

		bool ImGUIManager::CreateComponent(bool* p_open)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
			ImGui::Begin("Component", p_open);
			ImGui::End();

			return true;
		}

		void ImGUIManager::CreateDockingWindows()
		{
			CreateDockspace(&showDockspace);
			CreateConsole(&showConsole);
			CreateLog(&showLog);
			CreateComponent(&showComponent);
			CreateWindowWithImage(&showViewport);
		}

		void ImGUIManager::OnRender()
		{
			//Start Frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			CreateDockingWindows();

			//Render
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (m_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
		}
	}
}