#include "SceneManager.h"

namespace Queen
{
	namespace Managers
	{
		SceneManager::SceneManager()
		{

		}

		SceneManager::~SceneManager()
		{
			if(m_SceneQueue.size() > 0)
				ClearSceneQueue();
		
			QE_LOG(QE_TRACE, g_SCN_MAN_INFO_DESTROYED);
		}

		void SceneManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;

				QE_LOG(QE_TRACE, g_SCN_MAN_INFO_START);
			}
			else
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_ALREADY_STARTED);
			}
		}

		void SceneManager::Shutdown()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				QE_LOG(QE_WARN, g_SCN_MAN_INFO_SHUTDOWN);

				m_Running = false;
			}
		}

		void SceneManager::CreateScene(const char* sceneName)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_SceneQueue.find(sceneName) != m_SceneQueue.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "A scene with {v} as name, already exists.", sceneName);
				}
				else
				{
					Scenes::Scene* scene = new Scenes::Scene(sceneName);
					m_SceneQueue[sceneName] = scene;

					if (m_RenderScene == nullptr)
						m_RenderScene = scene;
				}
			}
		}

		void SceneManager::AddSceneToQueue(Scenes::Scene* scene)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_SceneQueue.find(scene->GetSceneConfiguration()->m_SceneName) != m_SceneQueue.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "A scene with {v} as name, already exists.", scene->GetSceneConfiguration()->m_SceneName);
				}
				else
				{
					m_SceneQueue[scene->GetSceneConfiguration()->m_SceneName] = scene;
				}
			}
		}

		void SceneManager::RemoveSceneFromQueue(const char* sceneName)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_SceneQueue.find(sceneName) == m_SceneQueue.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "A scene with {v} as name, do not exist.", sceneName);
				}
				else
				{
					delete m_SceneQueue.find(sceneName)->second;
					m_SceneQueue.erase(sceneName);
				}
			}
		}

		void SceneManager::ClearSceneQueue()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				for (auto& scene : m_SceneQueue)
				{
					delete scene.second;
				}

				m_SceneQueue.clear();
			}
		}

		bool SceneManager::CheckSceneExistence(const char* sceneName)
		{
			if (m_SceneQueue.find(sceneName) != m_SceneQueue.end())
				return true;
			else
			{ 
				QE_LOG_PARAMS(QE_ERROR, "Scene with name {v} do not exist", sceneName);
				return false;
			}
		}



		Scenes::Scene* SceneManager::GetRenderScene()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_RenderScene != nullptr)
					return m_RenderScene;
				else
				{
					QE_LOG(QE_ERROR, "Render Scene has not been setted!");
					QE_LOG(QE_WARN, "Checking if target is available to set as render...");

					if (m_RenderScene != nullptr)
					{
						QE_LOG(QE_ERROR, "Render Scene not setted");
						return nullptr;
					}
					else
						return m_RenderScene;
				}
			}			
			return nullptr;
		}

		Scenes::Scene* SceneManager::GetScene(const char* sceneName)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_SceneQueue.find(sceneName) == m_SceneQueue.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "A scene with {v} as name, do not exist.", sceneName);
				}
				else
				{
					return  m_SceneQueue.find(sceneName)->second;
				}
			}

			return nullptr;
		}

		void SceneManager::SetSceneAsRender(const char* sceneName)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_SceneQueue.find(sceneName) == m_SceneQueue.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "A scene with {v} as name, do not exist.", sceneName);
				}
				else
				{
					m_RenderScene = m_SceneQueue.find(sceneName)->second;
				}
			}
		}
		
		void SceneManager::SetRenderSceneWidth(float width)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				GetRenderScene()->GetSceneConfiguration()->m_Width = width;
			}
		}

		void SceneManager::SetRenderSceneHeight(float height)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				GetRenderScene()->GetSceneConfiguration()->m_Height = height;
			}
		}

		void SceneManager::SetRenderSceneLeft(float xpos)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				GetRenderScene()->GetSceneConfiguration()->m_Left = xpos;
			}
		}

		void SceneManager::SetRenderSceneRight(float xpos)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				GetRenderScene()->GetSceneConfiguration()->m_Right = xpos;
			}
		}

		void SceneManager::SetRenderSceneTop(float ypos)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				GetRenderScene()->GetSceneConfiguration()->m_Top = ypos;
			}
		}

		void SceneManager::SetRenderSceneBottom(float xpos)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				GetRenderScene()->GetSceneConfiguration()->m_Bottom = xpos;
			}
		}

		void SceneManager::SetSceneWidth(const char* sceneName, float width)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_SceneQueue.find(sceneName) == m_SceneQueue.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "Scene with name {v} does not exist", sceneName);
				}
				else
				{
					m_SceneQueue.find(sceneName)->second->GetSceneConfiguration()->m_Width = width;
				}
			}
		}

		void SceneManager::SetSceneHeight(const char* sceneName, float height)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_SceneQueue.find(sceneName) == m_SceneQueue.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "Scene with name {v} does not exist", sceneName);
				}
				else
				{
					m_SceneQueue.find(sceneName)->second->GetSceneConfiguration()->m_Height = height;
				}
			}
		}

		void SceneManager::SetRenderCamera(const char* cameraName)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_RenderScene->GetSceneConfiguration()->m_SceneCameras.find(cameraName) == m_RenderScene->GetSceneConfiguration()->m_SceneCameras.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "Camera with name {v} does not exist", cameraName);

					if (m_RenderScene->GetSceneConfiguration()->m_SceneCameras.size() > 0)
					{
						//Set first found camera as render camera
						m_RenderScene->GetSceneConfiguration()->m_TargetCamera = m_RenderScene->GetSceneConfiguration()->m_SceneCameras.begin()->second;
					}
				}
				else
				{
					m_RenderScene->GetSceneConfiguration()->m_TargetCamera = m_RenderScene->GetSceneConfiguration()->m_SceneCameras.find(cameraName)->second;
				}
			}
		}

		void SceneManager::SetMainCamera(const char* cameraName)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_RenderScene->GetSceneConfiguration()->m_SceneCameras.find(cameraName) == m_RenderScene->GetSceneConfiguration()->m_SceneCameras.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "Camera with name {v} does not exist", cameraName);
				}
				else
				{
					if (m_RenderScene->GetSceneConfiguration()->m_MainCamera != nullptr)
						m_RenderScene->GetSceneConfiguration()->m_SceneCameras.find(cameraName)->second->GetComponent<Entity::Component::Camera>()->m_IsMainCamera = false;
					
					m_RenderScene->GetSceneConfiguration()->m_MainCamera = m_RenderScene->GetSceneConfiguration()->m_SceneCameras.find(cameraName)->second;
					m_RenderScene->GetSceneConfiguration()->m_SceneCameras.find(cameraName)->second->GetComponent<Entity::Component::Camera>()->m_IsMainCamera = true;
				}
			}
		}
	}
}