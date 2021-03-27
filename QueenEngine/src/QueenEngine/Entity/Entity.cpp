#include "Entity.h"

namespace Queen
{
	namespace Entity
	{
		Entity::Entity(const char* name)
		{
			m_Name = name;

			// Adding default Components
			Component::Transform* transform = new Component::Transform;
			Component::Rotation* rotate = new Component::Rotation;
			Component::Scale* scale = new Component::Scale;

			AddComponent<Component::Transform>(transform);
			AddComponent<Component::Rotation>(rotate);
			AddComponent<Component::Scale>(scale);
		}

		Entity::~Entity()
		{
			RemoveAllComponent();
		}

		void Entity::LoadEntity()
		{
			m_VAO.CreateVertexArray();
			
			if (GetComponent<Component::Model>() != nullptr)
			{
				m_VBO.Create(GetComponent<Component::Model>()->m_Data);
				//m_IBO.Create(GetComponent<Component::Model>()->m_Indexes);
			}
			else
			{
				std::vector<Queen::Renderer::Vertex> vert2;
				std::vector<unsigned int> indexes = { 0 };

				m_VBO.Create(vert2);
				//m_IBO.Create(indexes);
			}

			m_VAO.Unbind();
			//m_IBO.Unbind();
			m_VBO.Unbind();
		}

		void Entity::LoadShader(const char* vertFilePath, const char* fragFilePath)
		{
			m_Shader.LoadShaders(vertFilePath, fragFilePath);
		}

		void Entity::Draw()
		{
			//Shader and Buffer Operations

			//m_VAO.Bind();
			//m_IBO.Bind();
			m_VBO.Bind();
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 6));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 3));

			if (GetComponent<Component::Model>() != nullptr) 
			{
				Component::Model* m = GetComponent<Component::Model>();

				glDrawArrays(GL_TRIANGLES, 0, m->m_Data.size());
				//glDrawElements(GL_TRIANGLES, GetComponent<Component::Model>()->m_Indexes.size(), GL_UNSIGNED_INT, nullptr);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0 ,0);
			}
				//glDrawElements(GL_TRIANGLES, 0, GL_UNSIGNED_INT, nullptr);

			glBindTexture(GL_TEXTURE_2D, 0);

			m_VBO.Unbind();
			//m_IBO.Unbind();
		}

		void Entity::SetTransform(glm::vec3 data)
		{
			GetComponent<Component::Transform>()->SetTransform(data);
		}

		void Entity::SetScale(glm::vec3 data)
		{
			GetComponent<Component::Scale>()->SetScale(data);
		}
	}
}