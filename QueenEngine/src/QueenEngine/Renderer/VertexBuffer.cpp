#include "VertexBuffer.h"
#include "iostream"

namespace Queen
{
	namespace Renderer
	{

		//Vertex Buffer
		VertexBuffer::VertexBuffer()
		{
			
		}

		VertexBuffer::~VertexBuffer()
		{

		}

		bool VertexBuffer::Create(std::vector<Vertex>& vertices)
		{
			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

			return true;
		}

		bool VertexBuffer::Bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			return true;
		}

		bool VertexBuffer::Unbind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			return true;
		}
	}
}