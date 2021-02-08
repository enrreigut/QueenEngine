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
			
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 6));

			return true;
		}

		bool IndexBuffer::Bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

			return true;
		}

		bool IndexBuffer::Unbind()
		{
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(2);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			return true;
		}
	}
}