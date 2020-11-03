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

		void Entity::LoadEntity(Renderer::VertexArray& va, float* verts, size_t sizeV, unsigned int* indices, size_t sizeI)
		{
			va.CreateVertexArray();
			m_VBO.Create(verts, sizeV);
			m_IBO.Create(indices, sizeI);
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

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glDisableVertexAttribArray(0);
		}
	}
}