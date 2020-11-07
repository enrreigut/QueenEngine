#include "Scenes.h"

namespace Queen
{
	namespace Scenes
	{
		Scene::Scene(std::string name)
		{
			m_SceneName = name;
			m_VAO = Renderer::VertexArray();
		}

		Scene::~Scene()
		{

		}

		void Scene::Load()
		{
			for (auto& elem : m_Entities)
			{
				elem.second->LoadEntity(m_VAO);
				elem.second->LoadShader("Resources/Shaders/Test/VertexShader.vert", "Resources/Shaders/Test/FragmentShader.frag");
			}
		}

		void Scene::RenderScene(Window::Window* w)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));

			Entity::Component::Camera* c_properties = m_Camera->GetComponent<Entity::Component::Camera>();
			c_properties->UpdateProjection(c_properties->FOV, (float) w->GetWidth() / (float)w->GetHeight(), c_properties->near, c_properties->far);
					
			for (auto& elem : m_Entities)
			{
				if(elem.second->GetComponent<Entity::Component::Model>() != nullptr)
				{
					elem.second->GetShader().SetMat4("u_Proj", c_properties->projection);
					elem.second->GetShader().SetMat4("u_View", view);
					elem.second->GetShader().SetMat4("u_Model", model);
					elem.second->Draw(m_VAO);
				}
			}
		}

		void Scene::AddEntity(Entity::Entity* e)
		{
			if (m_Entities.find(e->GetName()) == m_Entities.end())
			{
				m_Entities[e->GetName()] = e;
			}
		}

		void Scene::DeleteEntity(Entity::Entity* e)
		{
			if (m_Entities.find(e->GetName()) != m_Entities.end())
				m_Entities.erase(e->GetName());
		}
	}

}