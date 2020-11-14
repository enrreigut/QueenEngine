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
			Managers::EntityManager::Get().Start();
			Managers::SceneManager::Get().Start();

			//Create Window Application
			if (!Queen::Managers::WindowManager::Get().CreateWWindow(m_Title, m_Width, m_Height))
				exit(-1);

			//Init ImGUI
			m_Window = Queen::Managers::WindowManager::Get().GetWWindow(m_Title);
			Managers::ImGUIManager::Get().Init(m_Window, "#version 410");

			//Create Default Scene
			Queen::Managers::SceneManager::Get().CreateScene("Test Scene");
			Queen::Managers::WindowManager::Get().SetTargetWindow(Queen::Managers::WindowManager::Get().GetWWindow(m_Title));
			InitDefaultScene();
		}

		void Application::CameraControls()
		{
			//Rotation
			Entity::Component::Camera* camComponent = Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>();
			Entity::Component::Rotation* rotComponent = Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Rotation>();

			if (Queen::Managers::InputManager::Get().IsMouseButtonDown(GLFW_MOUSE_BUTTON_2))
			{
				int x = 0.0f, y = 0.0f;

				if (m_FirstMouse)
				{
					//Set to center of screen
					glfwSetInputMode(Queen::Managers::WindowManager::Get().GetWWindow(Queen::Managers::WindowManager::Get().GetTargetWindow()->GetWindowName())->GetWindowHandler(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

					glfwGetWindowPos(Queen::Managers::WindowManager::Get().GetWWindow(Queen::Managers::WindowManager::Get().GetTargetWindow()->GetWindowName())->GetWindowHandler(), &x, &y);

					float centerMousePosX = (Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_Left + (float)Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_Right) / 2.0f - (float)x;
					float centerMousePosY = (Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_Bottom + (float)Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_Top) / 2.0f - (float)y;
					glfwSetCursorPos(Queen::Managers::WindowManager::Get().GetWWindow(Queen::Managers::WindowManager::Get().GetTargetWindow()->GetWindowName())->GetWindowHandler(), centerMousePosX, centerMousePosY);

					m_FirstMouse = false;
				}
				else
				{
					//Set to center of screen
					glfwSetInputMode(Queen::Managers::WindowManager::Get().GetWWindow(Queen::Managers::WindowManager::Get().GetTargetWindow()->GetWindowName())->GetWindowHandler(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

					glfwGetWindowPos(Queen::Managers::WindowManager::Get().GetWWindow(Queen::Managers::WindowManager::Get().GetTargetWindow()->GetWindowName())->GetWindowHandler(), &x, &y);

					float centerMousePosX = (Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_Left + (float)Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_Right) / 2.0f - (float)x;
					float centerMousePosY = (Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_Bottom + (float)Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_Top) / 2.0f - (float)y;
					glfwSetCursorPos(Queen::Managers::WindowManager::Get().GetWWindow(Queen::Managers::WindowManager::Get().GetTargetWindow()->GetWindowName())->GetWindowHandler(), centerMousePosX, centerMousePosY);

					float precision = 0.5f;
					float xOffset = Queen::Managers::InputManager::Get().GetMousePosX() + precision - centerMousePosX;
					float yOffset = centerMousePosY - precision - Queen::Managers::InputManager::Get().GetMousePosY();

					rotComponent->m_Yaw += xOffset * m_DeltaTime * camComponent->m_Sensitivity;
					rotComponent->SetPitch(yOffset * m_DeltaTime * camComponent->m_Sensitivity);

					Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Rotation>()->m_Rotation.x = cos(glm::radians(rotComponent->m_Yaw)) * cos(glm::radians(rotComponent->m_Pitch));
					Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Rotation>()->m_Rotation.y = sin(glm::radians(rotComponent->m_Pitch));
					Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Rotation>()->m_Rotation.z = sin(glm::radians(rotComponent->m_Yaw)) * cos(glm::radians(rotComponent->m_Pitch));

					Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Rotation>()->m_Rotation = glm::normalize(Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Rotation>()->m_Rotation);
				}
			}

			if (Queen::Managers::InputManager::Get().IsMouseButtonUp(GLFW_MOUSE_BUTTON_2))
			{
				m_FirstMouse = true;
			}

			if (Queen::Managers::InputManager::Get().IsKeyPressed(Queen::Managers::WindowManager::Get().GetTargetWindow()->GetWindowHandler(), GLFW_KEY_LEFT_CONTROL))
			{
				//Scroll for FOV
				if (Queen::Managers::InputManager::Get().IsScrollUp())
					Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->SetFov(-m_DeltaTime * camComponent->m_ScrollSpeed);

				if (Queen::Managers::InputManager::Get().IsScrollDown())
					Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->SetFov(m_DeltaTime * camComponent->m_ScrollSpeed);

				//reset scroll input
				Queen::Managers::InputManager::Get().ResetScrollY();
			}
			else
			{
				//Movement
				if (Queen::Managers::InputManager::Get().IsKeyPressed(Queen::Managers::WindowManager::Get().GetTargetWindow()->GetWindowHandler(), GLFW_KEY_W))
					Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Transform>()->m_Transform += Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Rotation>()->m_Rotation * m_DeltaTime * camComponent->m_MoveSpeed;

				if (Queen::Managers::InputManager::Get().IsKeyPressed(Queen::Managers::WindowManager::Get().GetTargetWindow()->GetWindowHandler(), GLFW_KEY_A))
					Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Transform>()->m_Transform -= glm::normalize(glm::cross(Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Rotation>()->m_Rotation, glm::vec3(0.0f, 1.0f, 0.0f))) * m_DeltaTime * camComponent->m_MoveSpeed;

				if (Queen::Managers::InputManager::Get().IsKeyPressed(Queen::Managers::WindowManager::Get().GetTargetWindow()->GetWindowHandler(), GLFW_KEY_S))
					Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Transform>()->m_Transform -= Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Rotation>()->m_Rotation * m_DeltaTime * camComponent->m_MoveSpeed;

				if (Queen::Managers::InputManager::Get().IsKeyPressed(Queen::Managers::WindowManager::Get().GetTargetWindow()->GetWindowHandler(), GLFW_KEY_D))
					Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Transform>()->m_Transform += glm::normalize(glm::cross(Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Rotation>()->m_Rotation, glm::vec3(0.0f, 1.0f, 0.0f))) * m_DeltaTime * camComponent->m_MoveSpeed;
			}
		}

		void Application::InitDefaultScene()
		{
			//Init Configuration
			//Create Target Camera
			Entity::Entity* camera = Queen::Managers::EntityManager::Get().CreateCameraInRenderScene("QueenEngineCamera");
			camera->SetTransform(glm::vec3(7.0f, 5.0f, 5.0f));
			camera->GetComponent<Entity::Component::Rotation>()->SetRotation(glm::vec3(-0.8f, -0.4f, -0.4f));
			camera->GetComponent<Entity::Component::Rotation>()->m_Yaw = -140.0f;
			camera->GetComponent<Entity::Component::Rotation>()->SetPitch(-25);
			Queen::Managers::SceneManager::Get().SetRenderCamera("QueenEngineCamera");

			//Create Main Camera
			Entity::Entity* mainCamera = Queen::Managers::EntityManager::Get().CreateCameraInRenderScene("Camera");
			mainCamera->SetTransform(glm::vec3(0.0f, 0.0f, 5.0f));
			Queen::Managers::SceneManager::Get().SetMainCamera("Camera");

			//Create Entity
			Queen::Entity::Entity* e = Queen::Managers::EntityManager::Get().CreateEntityInRenderScene("Mario");
			Queen::Entity::Component::Model* m = new Queen::Entity::Component::Model;
			m->LoadObj("Resources/Model/Test/Mario.obj");
			e->AddComponent<Queen::Entity::Component::Model>(m);
		}

		void Application::Start()
		{			
			//Set to render the Scene with the Defult Flag
			Queen::Managers::RendererManager::Get().SetRenderScene();

			//Create Frame Buffer only if Debug is enabled
			if (m_Debug)
			{
				Queen::Managers::RendererManager::Get().CreateFrameBuffer(1080.0f, 720.0f);
				Queen::Managers::RendererManager::Get().RenderImGUI();
			}

			m_LastTime = glfwGetTime();
		}

		void Application::Shutdown()
		{
			Managers::SceneManager::Get().Shutdown(); 
			Managers::EntityManager::Get().Shutdown();
			Managers::ImGUIManager::Get().Shutdown(); 
			Managers::RendererManager::Get().Shutdown();
			Managers::EventManager::Get().Shutdown();
			Managers::WindowManager::Get().Shutdown();
			Managers::MemoryManager::Get().Shutdown();
			Managers::LogManager::Get().Shutdown();
		}

		void Application::LoadScene(Scenes::Scene& scene)
		{
			//Managers::SceneManager::Get().AddScene(&scene);
		}

		void Application::OnEvent()
		{
			/* HANDLE EVENTS OF ENITITES HERE */

			/*Scene Controls*/
			CameraControls();
			
			for (auto& ent : Queen::Managers::SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_SceneEntities)
			{
				ent.second->OnInput();
			}

		}

		void Application::Run()
		{
			while (Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->isRunning())
			{
				CalculateFPS();
	
				if (!m_Debug)
				{
					Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Render(m_Debug);

					Queen::Managers::RendererManager::Get().RenderScene(m_Debug);
				}
				else
				{
					//Start Rendering in FrameBuffer				
					Queen::Managers::RendererManager::Get().BindFrameBuffer();
					Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Render(m_Debug);
					
					//Render Scene
					//TODO: Change to Queen::Managers::RendererManager::Get().RenderScene(m_Debug, SceneManager::Get().GetDefaultScene())
					Queen::Managers::RendererManager::Get().RenderScene(m_Debug);

					//Stop Rendering in Frame Buffer				
					Queen::Managers::RendererManager::Get().UnbindFrameBuffer();
				
					//Render UI				
					Queen::Managers::RendererManager::Get().RenderImGUI();
				}
				
				this->OnEvent();
				
				Queen::Managers::WindowManager::Get().GetWWindow(m_Title)->Update();
			}
		}

		void Application::CalculateFPS()
		{
			double currentTime = glfwGetTime();
			m_Frames++;
			if (currentTime - m_LastTime >= 1.0) {
				// printf and reset
				QE_GUI_LOG_PARAMS(QE_SUCCESS, GUI::Logger::Get(), "FPS: {v}, {v} ms per frame", m_Frames, 1000.0 / double(m_Frames));

				m_DeltaTime = 1 / (float)m_Frames;

				m_Frames = 0;
				m_LastTime += 1.0;
			}
		}
	}
}