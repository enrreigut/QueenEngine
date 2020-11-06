#include "Entity.h"

namespace Queen
{
	namespace Entity
	{
		Entity::Entity(std::string name)
		{
			m_Name = name;
		}

		Entity::~Entity()
		{

		}

		void Entity::LoadEntity(Renderer::VertexArray& va)
		{
			va.CreateVertexArray();
			m_VBO.Create(m_Model.m_Vertices);
			m_IBO.Create(m_Model.m_Indexes);
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
			glDrawElements(GL_TRIANGLES, m_Model.m_Indexes.size(), GL_UNSIGNED_INT, nullptr);
			glDisableVertexAttribArray(0);
		}

		void Entity::AddModel(const char* filePath)
		{
			m_Model.LoadObj(filePath);
		}
	}
}