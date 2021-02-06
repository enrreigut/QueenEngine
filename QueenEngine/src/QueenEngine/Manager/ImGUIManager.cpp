#include "ImGUIManager.h"

namespace Queen
{
	namespace Managers
	{

		void DrawModelComponentInfo(Entity::Component::Component* c);
		void DrawTransformComponentInfo(Entity::Component::Component* c);
		void DrawRotationComponentInfo(Entity::Component::Component* c);
		void DrawScaleComponentInfo(Entity::Component::Component* c);
		void DrawCameraComponentInfo(Entity::Component::Component* c);

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

			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			if (!opt_padding)
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", p_open, window_flags);
			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

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
			
			ImVec2 vMin = ImGui::GetWindowContentRegionMin();
			ImVec2 vMax = ImGui::GetWindowContentRegionMax();

			SceneManager::Get().SetRenderSceneLeft(vMin.x + ImGui::GetWindowPos().x);
			SceneManager::Get().SetRenderSceneTop(vMin.y + ImGui::GetWindowPos().y);
			SceneManager::Get().SetRenderSceneRight(vMax.x + ImGui::GetWindowPos().x);
			SceneManager::Get().SetRenderSceneBottom(vMax.y + ImGui::GetWindowPos().y);

			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			SceneManager::Get().SetRenderSceneWidth(viewportPanelSize.x);
			SceneManager::Get().SetRenderSceneHeight(viewportPanelSize.y);

			if (m_ViewportSize != *((glm::vec2*)& ImGui::GetContentRegionAvail()))
			{
				m_FBO->Resize(m_ViewportSize);
				m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

				SceneManager::Get().SetRenderSceneWidth(viewportPanelSize.x);
				SceneManager::Get().SetRenderSceneHeight(viewportPanelSize.y);
			}

			ImGui::Image((void*)m_FBO->GetFBO(), viewportPanelSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			ImGui::End();
			ImGui::PopStyleVar();
			return true;
		}

		bool ImGUIManager::CreateSceneEntities(bool* p_open)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
			ImGui::Begin("Scene", p_open);

			auto targetScene = SceneManager::Get().GetRenderScene();

			ImGui::Text(targetScene->GetSceneConfiguration()->m_SceneName);
			
			ImGui::Separator();

			if (ImGui::CollapsingHeader("Camera Entities"))
			{
				for (auto& cam : targetScene->GetSceneConfiguration()->m_SceneCameras)
				{
					if (cam.second != targetScene->GetSceneConfiguration()->m_TargetCamera)
					{
						if (ImGui::TreeNode(cam.second->GetName()))
						{
							if (cam.second->GetComponent<Entity::Component::Transform>())
							{
								DrawTransformComponentInfo(cam.second->GetComponent<Entity::Component::Transform>());
							}

							if (cam.second->GetComponent<Entity::Component::Rotation>())
							{
								DrawRotationComponentInfo(cam.second->GetComponent<Entity::Component::Rotation>());
							}

							if (cam.second->GetComponent<Entity::Component::Scale>())
							{
								DrawScaleComponentInfo(cam.second->GetComponent<Entity::Component::Scale>());
							}

							if (cam.second->GetComponent<Entity::Component::Camera>())
							{
								DrawCameraComponentInfo(cam.second->GetComponent<Entity::Component::Camera>());
							}

							ImGui::TreePop();
						}
					}
				}
			}				

			if (ImGui::CollapsingHeader("Entities"))
			{
				for (auto ent : targetScene->GetSceneConfiguration()->m_SceneEntities)
				{
					if (ImGui::TreeNode(ent.second->GetName()))
					{
						if (ent.second->GetComponent<Entity::Component::Transform>())
						{
							DrawTransformComponentInfo(ent.second->GetComponent<Entity::Component::Transform>());
						}

						if (ent.second->GetComponent<Entity::Component::Rotation>())
						{
							DrawRotationComponentInfo(ent.second->GetComponent<Entity::Component::Rotation>());
						}

						if (ent.second->GetComponent<Entity::Component::Scale>())
						{
							DrawScaleComponentInfo(ent.second->GetComponent<Entity::Component::Scale>());
						}

						ImGui::TreePop();
					}
				}
			}
			
			ImGui::End();

			return true;
		}

		void ImGUIManager::CreateDockingWindows()
		{
			CreateDockspace(&showDockspace);
			CreateConsole(&showConsole);
			CreateLog(&showLog);
			CreateSceneEntities(&showSceneEntity);
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


		void DrawModelComponentInfo(Entity::Component::Component* c)
		{
			Entity::Component::Model* comp = (Entity::Component::Model*)c;

			if (ImGui::TreeNode("Model"))
			{
				ImGui::Text("Name: %s", comp->m_Name);

				ImGui::TreePop();
			}
		}

		void DrawTransformComponentInfo(Entity::Component::Component* c)
		{
			Entity::Component::Transform* comp = (Entity::Component::Transform*)c;

			if (ImGui::TreeNode("Transform"))
			{
				ImGui::PushItemWidth(-1);

				ImGui::Text("x");
				ImGui::InputFloat("x", &comp->m_Transform.x);

				ImGui::Text("y");
				ImGui::InputFloat("y", &comp->m_Transform.y);

				ImGui::Text("z");
				ImGui::InputFloat("z", &comp->m_Transform.z);

				ImGui::PopItemWidth();
				ImGui::TreePop();
			}			
		}

		void DrawRotationComponentInfo(Entity::Component::Component* c)
		{
			Entity::Component::Rotation* comp = (Entity::Component::Rotation*)c;

			if (ImGui::TreeNode("Rotation"))
			{
				ImGui::PushItemWidth(-1);

				ImGui::Text("x");
				ImGui::InputFloat("x", &comp->m_Rotation.x);

				ImGui::Text("y");
				ImGui::InputFloat("y", &comp->m_Rotation.y);

				ImGui::Text("z");
				ImGui::InputFloat("z", &comp->m_Rotation.z);

				ImGui::PopItemWidth();
				ImGui::TreePop();
			}
		}

		void DrawScaleComponentInfo(Entity::Component::Component* c)
		{
			Entity::Component::Scale* comp = (Entity::Component::Scale*)c;

			if (ImGui::TreeNode("Scale"))
			{
				ImGui::PushItemWidth(-1);

				ImGui::Text("x");
				ImGui::InputFloat("x", &comp->m_Scale.x);

				ImGui::Text("y");
				ImGui::InputFloat("y", &comp->m_Scale.y);

				ImGui::Text("z");
				ImGui::InputFloat("z", &comp->m_Scale.z);

				ImGui::PopItemWidth();
				ImGui::TreePop();
			}
		}

		void DrawCameraComponentInfo(Entity::Component::Component* c)
		{
			Entity::Component::Camera* comp = (Entity::Component::Camera*)c;

			if (ImGui::TreeNode("Configuration"))
			{
				ImGui::PushItemWidth(-1);

				ImGui::Text("FOV");
				ImGui::SliderFloat("FOV", &comp->m_FOV, 1.0f, 90.0f);

				ImGui::Text("Near");
				ImGui::InputFloat("Near", &comp->m_Near);

				ImGui::Text("Far");
				ImGui::InputFloat("Far", &comp->m_Far);

				ImGui::Checkbox("MainCamera", &comp->m_IsMainCamera);

				ImGui::PopItemWidth();
				ImGui::TreePop();
			}
		}
	}
}