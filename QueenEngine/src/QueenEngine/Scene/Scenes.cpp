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

		void Scene::RenderScene()
		{
			//TODO: Set Camera // Render Camaera
			//glm::mat4 proj = glm::perspective(glm::radians(40.0f), 4.0f/3.0f, 0.1f, 100.0f);
			glm::mat4 proj = glm::ortho(-10.0f, 10.f, 0.0f, 10.f, -1.0f, 10.0f);
			//glm::mat4 view = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
			//glm::mat4 MVP = proj * view;
			
			for (auto& elem : m_Entities)
			{
				elem.second->Draw(m_VAO);
				elem.second->GetShader().SetMat4("u_MVP", proj);
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