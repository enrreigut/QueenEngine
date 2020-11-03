#include "IndexBuffer.h"


namespace Queen
{
	namespace Renderer
	{

		IndexBuffer::IndexBuffer()
		{

		}

		IndexBuffer::~IndexBuffer()
		{

		}

		bool IndexBuffer::Create(unsigned int* indices, size_t& size)
		{
			glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
			return true;
		}

		bool IndexBuffer::Bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

			return true;
		}

		bool IndexBuffer::Unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			return true;
		}
	}
}