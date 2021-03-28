#include "ImGUIManager.h"

namespace Queen
{
	namespace Managers
	{
		void DrawModelComponentInfo(Entity::Component::Component* c);
		void DrawVec3ComponentInfo(const char*label, glm::vec3& transform, float resetValue = 0.0f);
		void DrawLightColorComponentInfo(const char* label, Entity::Component::Component* c, float resetValue = 0.0f);
		void DrawCameraComponentInfo(Entity::Component::Component* c);
		void DrawGridInfo(Scenes::Debug::Grid* grid);
		void DrawMaterialInfo(Entity::Component::Component* c);

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

		bool ImGUIManager::CreateRunStop(bool* p_open)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar;

			ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
			ImGui::Begin("Play/Run", p_open, window_flags);


			if (ImGui::Button("Play"))
			{
				m_isPlayingGame = true;
			}

			ImGui::SameLine();

			if (ImGui::Button("Stop"))
			{
				m_isPlayingGame = false;
			}

			ImGui::PopStyleVar();
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

			if (m_ViewportSize != *((glm::vec2*) &ImGui::GetContentRegionAvail()))
			{
				m_FBO->Resize(*((glm::vec2*) &ImGui::GetContentRegionAvail()));
				m_ViewportSize = { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y };

				SceneManager::Get().SetRenderSceneWidth(m_ViewportSize.x);
				SceneManager::Get().SetRenderSceneHeight(m_ViewportSize.y);

				EntityManager::Get().CalculateCamera(true);
			}

			glm::mat4 identity = glm::mat4(1.0f);
			
			ImGui::Image((void*)m_FBO->GetFBO(), viewportPanelSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
			ImGui::End();

			//Update View and Manipulate
			ImGuizmo::ViewManipulate(
				&SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->m_View[0][0],
				8.0f,
				ImVec2(SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_Right - 128, SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_Top),
				ImVec2(128, 128),
				0x10101010
			);

			ImGui::PopStyleVar();
			return true;
		}

		bool ImGUIManager::CreateEntitiySpecifications(bool* p_open)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
			ImGui::Begin("Specifications", p_open);

			ImGui::Text("Select an Entity...");
			ImGui::Separator();

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
			
			if (ImGui::CollapsingHeader("Scene Configuration"))
			{
				//Scene Configuration
				if (targetScene->GetSceneConfiguration()->m_TargetCamera != nullptr)
				{
					//SetUp Selection
					if(ImGui::Selectable(targetScene->GetSceneConfiguration()->m_TargetCamera->GetName(), m_Selected == targetScene->GetSceneConfiguration()->m_TargetCamera->GetName()))
						m_Selected = targetScene->GetSceneConfiguration()->m_TargetCamera->GetName();

					if (ImGui::Selectable("Grid", m_Selected == "Grid"))
						m_Selected = "Grid";
					
					//Camera
					if (m_Selected == targetScene->GetSceneConfiguration()->m_TargetCamera->GetName())
					{
						ImGui::Begin("Specifications", p_open, ImGuiWindowFlags_AlwaysAutoResize);
												
						ImGui::PushItemWidth(ImGui::GetWindowWidth()-105);
						ImGui::InputText("##EntityName", (char*)targetScene->GetSceneConfiguration()->m_TargetCamera->GetName(),255);
						ImGui::PopItemWidth();
						ImGui::SameLine();
						ImGui::SetCursorPosX(ImGui::GetWindowWidth()-100);
						ImGui::Button("Add Component");
						ImGui::Separator();

						//Transform data
						if (ImGui::CollapsingHeader("Transform"))
						{
							if (targetScene->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Transform>())
							{
								DrawVec3ComponentInfo("Translation", targetScene->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Transform>()->m_Transform);
							}

							if (targetScene->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Rotation>())
							{
								DrawVec3ComponentInfo("Rotation", targetScene->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Rotation>()->m_Rotation);
							}					
						}

						ImGui::Separator();

						if (ImGui::CollapsingHeader("Configuration"))
						{
							if (targetScene->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>())
							{
								DrawCameraComponentInfo(targetScene->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>());
							}
						}

						ImGui::Separator();
						ImGui::End();
					}					
				}

				//Grid
				if (targetScene->GetSceneConfiguration()->m_Grid != nullptr)
				{
					if(m_Selected == "Grid")
					{
						ImGui::Begin("Specifications", p_open);

						ImGui::SetNextItemOpen(true);
						if (ImGui::TreeNode("Grid"))
						{	
							ImGui::PushItemWidth(-1);
							DrawGridInfo(targetScene->GetSceneConfiguration()->m_Grid);
							ImGui::TreePop();
							ImGui::PopItemWidth();
						}

						ImGui::Separator();

						ImGui::End();
					}
				}
			}

			//Cam Entities
			if (ImGui::CollapsingHeader("Camera Entities"))
			{
				for (auto& cam : targetScene->GetSceneConfiguration()->m_SceneCameras)
				{
					if (cam.second != targetScene->GetSceneConfiguration()->m_TargetCamera)
					{
						if (ImGui::Selectable(cam.second->GetName(), m_Selected == cam.second->GetName()))
							m_Selected = cam.second->GetName();

						if (m_Selected == cam.second->GetName())
						{
							ImGui::Begin("Specifications", p_open, ImGuiWindowFlags_AlwaysAutoResize);

							ImGui::PushItemWidth(ImGui::GetWindowWidth() - 105);
							ImGui::InputText("##EntityName", (char*)cam.second->GetName(), 255);
							ImGui::PopItemWidth();
							ImGui::SameLine();
							ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 100);
							ImGui::Button("Add Component");
							ImGui::Separator();

							if (ImGui::CollapsingHeader("Transform"))
							{

								if (cam.second->GetComponent<Entity::Component::Transform>())
								{
									DrawVec3ComponentInfo("Translation", cam.second->GetComponent<Entity::Component::Transform>()->m_Transform);
								}

								if (cam.second->GetComponent<Entity::Component::Rotation>())
								{
									DrawVec3ComponentInfo("Rotation", cam.second->GetComponent<Entity::Component::Rotation>()->m_Rotation);
								}
							}

							ImGui::Separator();
							ImGui::End();
						}
					}
				}
			}				

			//Entities
			if (ImGui::CollapsingHeader("Entities"))
			{
				for (auto ent : targetScene->GetSceneConfiguration()->m_SceneEntities)
				{
					if (ImGui::Selectable(ent.second->GetName(), m_Selected == ent.second->GetName()))
						m_Selected = ent.second->GetName();

					if (m_Selected == ent.second->GetName())
					{
						ImGui::Begin("Specifications", p_open, ImGuiWindowFlags_AlwaysAutoResize);

						ImGui::PushItemWidth(ImGui::GetWindowWidth() - 105);
						ImGui::InputText("##EntityName", (char*)ent.second->GetName(), 255);
						ImGui::PopItemWidth();
						ImGui::SameLine();
						ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 100);
						ImGui::Button("Add Component");
						ImGui::Separator();

						if (ImGui::CollapsingHeader("Transform"))
						{

							if (ent.second->GetComponent<Entity::Component::Transform>())
							{
								DrawVec3ComponentInfo("Translation", ent.second->GetComponent<Entity::Component::Transform>()->m_Transform);
							}

							if (ent.second->GetComponent<Entity::Component::Rotation>())
							{
								DrawVec3ComponentInfo("Rotation", ent.second->GetComponent<Entity::Component::Rotation>()->m_Rotation);
							}

							if (ent.second->GetComponent<Entity::Component::Scale>())
							{
								DrawVec3ComponentInfo("Scale", ent.second->GetComponent<Entity::Component::Scale>()->m_Scale, 1.0f);
							}
						}

						ImGui::Separator();

						if (ent.second->GetComponent<Entity::Component::Material>())
						{
							if (ImGui::CollapsingHeader("Material"))
							{							
								DrawMaterialInfo(ent.second->GetComponent<Entity::Component::Material>());
							}
						}

						ImGui::Separator();

						if (ent.second->GetComponent<Queen::Entity::Component::PointLight>())
						{
							if (ImGui::CollapsingHeader("Light Properties"))
							{
								DrawLightColorComponentInfo("Color", ent.second->GetComponent<Entity::Component::PointLight>(), 0.5f);
							}
						}

						ImGui::Separator();

						ImGui::End();
					}
				}
			}
			
			ImGui::End();

			return true;
		}

		void ImGUIManager::CreateDockingWindows()
		{
			CreateDockspace(&showDockspace);
			CreateRunStop(&showRunStop);
			CreateConsole(&showConsole);
			CreateLog(&showLog);
			CreateEntitiySpecifications(&showEntitySpec);
			CreateSceneEntities(&showSceneEntity);
			CreateWindowWithImage(&showViewport);
		}

		void ImGUIManager::OnRender()
		{
			//Start Frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::BeginFrame();
			ImGuizmo::Enable(true);

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

			if(m_IsFirstRender)
				m_IsFirstRender = false;
		}

		void DrawGridInfo(Scenes::Debug::Grid* grid)
		{
			int actualWidth = grid->m_Width;
			int actualHeight = grid->m_Height;
			int actualResolution = grid->m_Resolution;

			ImGui::PushItemWidth(-1);
			
			ImGui::Text("Width");
			ImGui::InputInt("##w", &grid->m_Width);

			ImGui::Text("Height");
			ImGui::InputInt("##h", &grid->m_Height);

			ImGui::Text("Resolution");
			ImGui::InputInt("##r", &grid->m_Resolution);

			if (ImGui::TreeNode("Transform"))
			{
				ImGui::Text("x");
				ImGui::InputFloat("x", &grid->m_Transform.x);

				ImGui::Text("y");
				ImGui::InputFloat("y", &grid->m_Transform.y);

				ImGui::Text("z");
				ImGui::InputFloat("z", &grid->m_Transform.z);

				ImGui::TreePop();
			}

			ImGui::PopItemWidth();

			if (actualWidth != grid->m_Width || actualHeight != grid->m_Height || actualResolution != grid->m_Resolution)
				grid->UpdateGrid();

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

		void DrawVec3ComponentInfo(const char* label, glm::vec3& transform, float resetValue)
		{
			float buttonHeight = ImGui::GetFont()->FontSize + ImGui::GetStyle().FramePadding.y * 2.0f;
			float buttonWidth = buttonHeight + 3.0f;

			ImColor r = ImColor(239, 118, 122);
			ImColor g = ImColor(73, 190, 170);
			ImColor b = ImColor(69, 105, 144);

			if (ImGui::TreeNode(label))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 10 });

				//X
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)r);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)r);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)r);
				if (ImGui::Button("X", ImVec2{ buttonWidth, buttonHeight }))
					transform.x = resetValue;
				ImGui::PopStyleColor(3);

				ImGui::SameLine();
				//ImGui::PushItemWidth(-1);
				ImGui::DragFloat("##X", &transform.x, 0.1f);
				//ImGui::PopItemWidth();

				//Y
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)g);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)g);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)g);
				if (ImGui::Button("Y", ImVec2{ buttonWidth, buttonHeight }))
					transform.y = resetValue;
				ImGui::PopStyleColor(3);

				ImGui::SameLine();
				//ImGui::PushItemWidth(-1);
				ImGui::DragFloat("##Y", &transform.y, 0.1f);
				//ImGui::PopItemWidth();

				//Z
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)b);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)b);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)b);
				if (ImGui::Button("Z", ImVec2{ buttonWidth, buttonHeight }))
					transform.z = resetValue;
				ImGui::PopStyleColor(3);

				ImGui::SameLine();
				//ImGui::PushItemWidth(-1);
				ImGui::DragFloat("##Z", &transform.z, 0.1f);
				//ImGui::PopItemWidth();

				ImGui::PopStyleVar();
				ImGui::TreePop();
			}

		}

		void DrawRotationComponentInfo(Entity::Component::Component* c)
		{
			Entity::Component::Rotation* comp = (Entity::Component::Rotation*)c;

			if (ImGui::TreeNode("Rotation"))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

				//X
				if (ImGui::Button("X##RotButX"))
					comp->m_Rotation.x = 0;

				ImGui::SameLine();
				ImGui::DragFloat("##RotX", &comp->m_Rotation.x, 0.1f);

				//Y
				if (ImGui::Button("Y##RotButY"))
					comp->m_Rotation.y = 0;

				ImGui::SameLine();
				ImGui::DragFloat("##RotY", &comp->m_Rotation.y, 0.1f);

				//Z
				if (ImGui::Button("Z##RotButZ"))
					comp->m_Rotation.z = 0;

				ImGui::SameLine();
				ImGui::DragFloat("##RotZ", &comp->m_Rotation.z, 0.1f);

				ImGui::PopStyleVar();
				ImGui::TreePop();
			}
		}

		void DrawScaleComponentInfo(Entity::Component::Component* c)
		{
			Entity::Component::Scale* comp = (Entity::Component::Scale*)c;

			if (ImGui::TreeNode("Scale"))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

				//X
				if (ImGui::Button("X##ScaButX"))
					comp->m_Scale.x = 0;

				ImGui::SameLine();
				ImGui::DragFloat("##ScaX", &comp->m_Scale.x, 0.1f);

				//Y
				if (ImGui::Button("Y##ScaButY"))
					comp->m_Scale.y = 0;

				ImGui::SameLine();
				ImGui::DragFloat("##ScaY", &comp->m_Scale.y, 0.1f);

				//Z
				if (ImGui::Button("Z##ScaButZ"))
					comp->m_Scale.z = 0;

				ImGui::SameLine();
				ImGui::DragFloat("##ScaZ", &comp->m_Scale.z, 0.1f);

				ImGui::PopStyleVar();
				ImGui::TreePop();
			}
		}

		void DrawCameraComponentInfo(Entity::Component::Component* c)
		{
			Entity::Component::Camera* comp = (Entity::Component::Camera*)c;

			ImGui::PushItemWidth(-1);

			ImGui::Text("FOV");
			ImGui::SliderFloat("##FOV", &comp->m_FOV, 1.0f, 90.0f);

			ImGui::Text("Near");
			ImGui::InputFloat("##Near", &comp->m_Near);

			ImGui::Text("Far");
			ImGui::InputFloat("##Far", &comp->m_Far);

			ImGui::Checkbox("MainCamera", &comp->m_IsMainCamera);

			ImGui::PopItemWidth();
		}

		void DrawLightColorComponentInfo(const char* label, Entity::Component::Component* c, float resetValue)
		{
			Entity::Component::PointLight* comp = (Entity::Component::PointLight*)c;

			if (ImGui::TreeNode(label))
			{
				ImGui::ColorPicker4("Color", &comp->lightColor[0]);

				ImGui::TreePop();
			}
		}

		void DrawMaterialInfo(Entity::Component::Component* c)
		{
			Entity::Component::Material* comp = (Entity::Component::Material*)c;

			ImGui::PushItemWidth(-1);

			ImGui::Text("Ambient Strength");
			ImGui::SliderFloat("##ambStr", &comp->ambientStrength, 0.0f, 1.0f);

			ImGui::Text("Specular Strength");
			ImGui::SliderFloat("##specStr", &comp->specularStrength, 0.0f, 1.0f);

			ImGui::Image((void*)(intptr_t)comp->texture->m_Texture->GetTextureId(), ImVec2{ 255.0f, 255.0f });
		}
	}
}