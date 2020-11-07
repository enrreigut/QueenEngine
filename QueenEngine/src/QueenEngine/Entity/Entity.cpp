#include "Entity.h"

namespace Queen
{
	namespace Entity
	{
		Entity::Entity(std::string name)
		{
			m_Name = name;

			Component::Transform transform;
			AddComponent<Component::Transform>(&transform);
		}

		Entity::~Entity()
		{

		}

		void Entity::LoadEntity(Renderer::VertexArray& va)
		{
			va.CreateVertexArray();
			
			if (GetComponent<Component::Model>() != nullptr)
			{
				m_VBO.Create(GetComponent<Component::Model>()->m_Vertices);
				m_IBO.Create(GetComponent<Component::Model>()->m_Indexes);
			}
			else
			{
				std::vector<glm::vec3> vert = { glm::vec3(0.0f,0.0f,0.0f) };
				std::vector<unsigned int> indexes = { 0 };

				m_VBO.Create(vert);
				m_IBO.Create(indexes);
			}
		}

		void Entity::LoadShader(const char* vertFilePath, const char* fragFilePath)
		{
			m_Shader.LoadShaders(vertFilePath, fragFilePath);
		}

		void Entity::Draw(Renderer::VertexArray& va)
		{
			glUseProgram(m_Shader.GetProgramID());

			glEnableVertexAttribArray(0);

			m_VBO.Bind();
			m_IBO.Bind();

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glDrawElements(GL_TRIANGLES, GetComponent<Component::Model>()->m_Indexes.size(), GL_UNSIGNED_INT, nullptr);
			glDisableVertexAttribArray(0);
		}
	}
}