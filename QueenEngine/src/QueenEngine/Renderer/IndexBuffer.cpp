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

		bool IndexBuffer::Create(std::vector<unsigned int>& indices)
		{
			glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
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