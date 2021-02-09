#include "EntityManager.h"

namespace Queen
{
	namespace Managers
	{
		EntityManager::EntityManager()
		{

		}

		EntityManager::~EntityManager()
		{
			QE_LOG(QE_TRACE, g_ENT_MAN_INFO_DESTROYED);
		}

		void EntityManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;

				QE_LOG(QE_TRACE, g_ENT_MAN_INFO_START);
			}
			else
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_ALREADY_STARTED);
			}
		}

		void EntityManager::Shutdown()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				QE_LOG(QE_WARN, g_ENT_MAN_INFO_SHUTDOWN);

				m_Running = false;
			}
		}

		//Scene existence should be checked 
		void AddEntity(Scenes::Scene* scene, Entity::Entity* entity)
		{
			auto sceneToAdd = SceneManager::Get().GetScene(scene->GetSceneConfiguration()->m_SceneName);	
			bool isCamera = false;
				
			if (entity->GetComponent<Entity::Component::Camera>() != nullptr)
				isCamera = true;
			
			if(isCamera)
			{
				if (sceneToAdd->GetSceneConfiguration()->m_SceneCameras.find(entity->GetName()) != sceneToAdd->GetSceneConfiguration()->m_SceneCameras.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "There is already a camera with the name {v} in the scene {v}", entity->GetName(), sceneToAdd->GetSceneConfiguration()->m_SceneName);
				}
				else
				{
					SceneManager::Get().GetScene(scene->GetSceneConfiguration()->m_SceneName)->GetSceneConfiguration()->m_SceneCameras[entity->GetName()] = entity;
				}
			}
			else
			{
				if (sceneToAdd->GetSceneConfiguration()->m_SceneEntities.find(entity->GetName()) != sceneToAdd->GetSceneConfiguration()->m_SceneEntities.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "There is already an entity with the name {v} in the scene {v}", entity->GetName(), sceneToAdd->GetSceneConfiguration()->m_SceneName);
				}
				else
				{
					SceneManager::Get().GetScene(scene->GetSceneConfiguration()->m_SceneName)->GetSceneConfiguration()->m_SceneEntities[entity->GetName()] = entity;
				}
			}
		}

		Entity::Entity* EntityManager::CreateCamera(Scenes::Scene* scene, const char* entityName)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (SceneManager::Get().CheckSceneExistence(scene->GetSceneConfiguration()->m_SceneName))
				{
					auto SceneCameras = SceneManager::Get().GetScene(scene->GetSceneConfiguration()->m_SceneName)->GetSceneConfiguration()->m_SceneCameras;
				
					if (SceneCameras.find(entityName) != SceneCameras.end())
					{
						QE_LOG_PARAMS(QE_ERROR, "There is already a camera with the name {v} in the scene {v}", entityName, scene->GetSceneConfiguration()->m_SceneName);
					}
					else
					{
						Entity::Entity* camera = new Entity::Entity(entityName);
						camera->SetTransform(glm::vec3(0.0f, 0.0f, -10.0f));
						Entity::Component::Camera* camComp = new Entity::Component::Camera();
						camera->AddComponent<Entity::Component::Camera>(camComp);

						SceneManager::Get().GetScene(scene->GetSceneConfiguration()->m_SceneName)->GetSceneConfiguration()->m_SceneCameras[camera->GetName()] = camera;

						return camera;
					}
				}
			}

			return nullptr;
		}

		Entity::Entity* EntityManager::CreateEntity(Scenes::Scene* scene, const char* entityName)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (SceneManager::Get().CheckSceneExistence(scene->GetSceneConfiguration()->m_SceneName))
				{
					auto SceneEntities = SceneManager::Get().GetScene(scene->GetSceneConfiguration()->m_SceneName)->GetSceneConfiguration()->m_SceneEntities;
					
					if (SceneEntities.find(entityName) != SceneEntities.end())
					{
						QE_LOG_PARAMS(QE_ERROR, "There is already an Entity with the name {v} in the scene {v}", entityName, scene->GetSceneConfiguration()->m_SceneName);
					}
					else
					{
						Entity::Entity* entity = new Entity::Entity(entityName);
						SceneManager::Get().GetScene(scene->GetSceneConfiguration()->m_SceneName)->GetSceneConfiguration()->m_SceneEntities[entity->GetName()] = entity;

						return entity;
					}
				}
			}

			return nullptr;
		}

		Entity::Entity* EntityManager::CreateCamera(const char* sceneName, const char* entityName)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (SceneManager::Get().CheckSceneExistence(sceneName))
				{
					auto scene = SceneManager::Get().GetScene(sceneName);
				
					if (scene->GetSceneConfiguration()->m_SceneCameras.find(entityName) != scene->GetSceneConfiguration()->m_SceneCameras.end())
					{
						QE_LOG_PARAMS(QE_ERROR, "There is already a camera with the name {v} in the scene {v}", entityName, sceneName);
					}
					else
					{
						Entity::Entity* camera = new Entity::Entity(entityName);
						camera->SetTransform(glm::vec3(0.0f, 0.0f, -10.0f));
						Entity::Component::Camera* camComp = new Entity::Component::Camera();
						camera->AddComponent<Entity::Component::Camera>(camComp);

						SceneManager::Get().GetScene(sceneName)->GetSceneConfiguration()->m_SceneCameras[camera->GetName()] = camera;

						return camera;
					}
				}
			}

			return nullptr;
		}

		Entity::Entity* EntityManager::CreateEntity(const char* sceneName, const char* entityName)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_NOT_STARTED);
			}
			else
			{				
				if (SceneManager::Get().CheckSceneExistence(sceneName))
				{
					auto scene = SceneManager::Get().GetScene(sceneName);

					if (scene->GetSceneConfiguration()->m_SceneEntities.find(entityName) != scene->GetSceneConfiguration()->m_SceneEntities.end())
					{
						QE_LOG_PARAMS(QE_ERROR, "There is already an entity with the name {v} in the scene {v}", entityName, sceneName);
					}
					else
					{
						Entity::Entity* entity = new Entity::Entity(entityName);
						SceneManager::Get().GetScene(sceneName)->GetSceneConfiguration()->m_SceneEntities[entity->GetName()] = entity;

						return entity;
					}
				}				
			}
			
			return nullptr;
		}

		Entity::Entity* EntityManager::CreateCameraInRenderScene(const char* entityName)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_NOT_STARTED);
				return nullptr;
			}
			else
			{
				if (SceneManager::Get().CheckSceneExistence(SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_SceneName))
				{
					auto scene = SceneManager::Get().GetRenderScene();

					if (scene->GetSceneConfiguration()->m_SceneCameras.find(entityName) != scene->GetSceneConfiguration()->m_SceneCameras.end())
					{
						QE_LOG_PARAMS(QE_ERROR, "There is already a camera with the name {v} in the scene {v}", entityName, scene->GetSceneConfiguration()->m_SceneName);
					}
					else
					{
						Entity::Entity* camera = new Entity::Entity(entityName);
						camera->SetTransform(glm::vec3(0.0f, 0.0f, 10.0f));
						Entity::Component::Camera* camComp = new Entity::Component::Camera();
						camera->AddComponent<Entity::Component::Camera>(camComp);

						SceneManager::Get().GetScene(scene->GetSceneConfiguration()->m_SceneName)->GetSceneConfiguration()->m_SceneCameras[camera->GetName()] = camera;

						return camera;
					}
				}
			}			
			return nullptr;
		}

		Entity::Entity* EntityManager::CreateEntityInRenderScene(const char* entityName)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_NOT_STARTED);
				return nullptr;
			}
			else
			{
				if (SceneManager::Get().CheckSceneExistence(SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_SceneName))
				{
					auto scene = SceneManager::Get().GetRenderScene();

					if (scene->GetSceneConfiguration()->m_SceneEntities.find(entityName) != scene->GetSceneConfiguration()->m_SceneEntities.end())
					{
						QE_LOG_PARAMS(QE_ERROR, "There is already an entity with the name {v} in the scene {v}", entityName, scene->GetSceneConfiguration()->m_SceneName);
					}
					else
					{
						Entity::Entity* entity = new Entity::Entity(entityName);
						SceneManager::Get().GetScene(scene->GetSceneConfiguration()->m_SceneName)->GetSceneConfiguration()->m_SceneEntities[entity->GetName()] = entity;

						return entity;
					}
				}
			}

			return nullptr;
		}

		void EntityManager::AddEntity(Scenes::Scene* scene, Entity::Entity* entity)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (SceneManager::Get().CheckSceneExistence(scene->GetSceneConfiguration()->m_SceneName))
				{
					AddEntity(scene->GetSceneConfiguration()->m_SceneName, entity);
				}
			}
		}

		void EntityManager::AddEntity(const char* sceneName, Entity::Entity* entity)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (SceneManager::Get().CheckSceneExistence(sceneName))
				{
					AddEntity(sceneName, entity);
				}
			}
		}

		void EntityManager::AddEntityToRenderScene(Entity::Entity* entity)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (SceneManager::Get().CheckSceneExistence(SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_SceneName))
				{
					AddEntity(SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_SceneName, entity);
				}
			}
		}

		void EntityManager::CalculateCamera(bool debugRender)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				//Set Correct Aspect Ratio if we are in debugMode or not
				if (debugRender)
				{
					SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->UpdateProjection(
						SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->m_FOV, 
						SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_Width / SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_Height, 
						SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->m_Near, 
						SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->m_Far
					);					
				}
				else
					SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->UpdateProjection(
						SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->m_FOV,
						(float)WindowManager::Get().GetTargetWindow()->GetWidth() / (float)WindowManager::Get().GetTargetWindow()->GetHeight(), 
						SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->m_Near,
						SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->m_Far);
			}
		}

		void EntityManager::DrawEntity(Entity::Entity* entity)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_ENT_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				glUseProgram(entity->GetShader().GetProgramID());

				glm::mat4 model = glm::mat4(1.0f);
				
				if (entity->GetComponent<Entity::Component::Model>() != nullptr)
				{
					entity->GetShader().SetMat4("u_Proj", SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->m_Projection);
					entity->GetShader().SetMat4("u_View", SceneManager::Get().GetRenderScene()->GetSceneConfiguration()->m_TargetCamera->GetComponent<Entity::Component::Camera>()->m_View);
					
					model = glm::translate(model, entity->GetComponent<Entity::Component::Transform>()->m_Transform);
					model = glm::scale(model, entity->GetComponent<Entity::Component::Scale>()->m_Scale);

					//RotateX
					model = glm::rotate(model, entity->GetComponent<Entity::Component::Rotation>()->m_Rotation.x * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
					//RotateY
					model = glm::rotate(model, entity->GetComponent<Entity::Component::Rotation>()->m_Rotation.y * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
					//Rotate Z
					model = glm::rotate(model, entity->GetComponent<Entity::Component::Rotation>()->m_Rotation.z * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));
					
					entity->GetShader().SetMat4("u_Model", model);
				}

				if (entity->GetComponent<Entity::Component::Texture>() != nullptr)
				{
					entity->GetComponent<Entity::Component::Texture>()->Bind(0);
				}

				entity->Draw();

				glUseProgram(0);
			}
		}
	}
}