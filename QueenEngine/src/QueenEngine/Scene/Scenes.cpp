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
				elem.second->LoadEntity(m_VAO, elem.second->m_Data, sizeof(elem.second->m_Data), elem.second->indices, sizeof(elem.second->indices));
				elem.second->LoadShader("Resources/Shaders/Test/VertexShader.vert",
					"Resources/Shaders/Test/FragmentShader.frag");
			}
		}

		void Scene::RenderScene()
		{
			for (auto& elem : m_Entities)
				elem.second->Draw(m_VAO);
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