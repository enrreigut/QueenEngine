#include "Scenes.h"

namespace Queen
{
	namespace Scenes
	{
		Scene::Scene(const char* name)
		{
			m_SceneConfiguration = new SceneComponentElement;
			m_SceneConfiguration->m_SceneName = name;
		}

		Scene::~Scene()
		{

		}

		void Scene::Load()
		{
			//SetUp View Camera

			if (m_SceneConfiguration->m_TargetCamera != nullptr)
			{
				m_SceneConfiguration->m_TargetCamera->GetComponent<Entity::Component::Camera>()->m_View = glm::lookAt(
					m_SceneConfiguration->m_TargetCamera->GetComponent<Entity::Component::Transform>()->m_Transform,
					m_SceneConfiguration->m_TargetCamera->GetComponent<Entity::Component::Transform>()->m_Transform + m_SceneConfiguration->m_TargetCamera->GetComponent<Entity::Component::Rotation>()->m_Rotation,
					glm::vec3(0.0f, 1.0f, 0.0f)
				);
			}

			//Load Debug
			m_SceneConfiguration->m_Grid = new Debug::Grid;
			m_SceneConfiguration->m_Grid->CalculateGrid();
			m_SceneConfiguration->m_Grid->CreateGrid();

			//Load Entities
			for (auto& elem : m_SceneConfiguration->m_SceneEntities)
			{
				elem.second->LoadEntity();

				if(elem.second->GetComponent<Queen::Entity::Component::PointLight>() != nullptr)
					elem.second->LoadShader("Resources/Shaders/LightShader/VertexShader.vert", "Resources/Shaders/LightShader/FragmentShader.frag");
				else
					elem.second->LoadShader("Resources/Shaders/TextureShader/VertexShader.vert", "Resources/Shaders/TextureShader/FragmentShader.frag");
			}
		}

		void Scene::DrawDebug()
		{

			//Draw Grid

			glUseProgram(m_SceneConfiguration->m_Grid->m_Shader.GetProgramID());

			m_SceneConfiguration->m_Grid->m_Shader.SetMat4("u_Proj", m_SceneConfiguration->m_TargetCamera->GetComponent<Entity::Component::Camera>()->m_Projection);
			m_SceneConfiguration->m_Grid->m_Shader.SetMat4("u_View", m_SceneConfiguration->m_TargetCamera->GetComponent<Entity::Component::Camera>()->m_View);
			glm::mat4 model(1.0f);
			model = glm::translate(model, m_SceneConfiguration->m_Grid->m_Transform);
			m_SceneConfiguration->m_Grid->m_Shader.SetMat4("u_Model", model);

			glBindVertexArray(m_SceneConfiguration->m_Grid->m_VaoId);

			glDrawElements(GL_LINES, m_SceneConfiguration->m_Grid->m_GridIndeces.size() * 4, GL_UNSIGNED_INT, nullptr);

			glBindVertexArray(0);

			glUseProgram(0);
		}
	}
}