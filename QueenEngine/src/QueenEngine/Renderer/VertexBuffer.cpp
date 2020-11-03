#include "VertexBuffer.h"


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

		bool VertexBuffer::Create(float* vertices, size_t& size)
		{
			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

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