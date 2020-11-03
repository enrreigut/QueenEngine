#include "VertexArray.h"

namespace Queen
{
	namespace Renderer
	{

		VertexArray::VertexArray()
		{
			
		}

		VertexArray::~VertexArray()
		{
			
		}

		void VertexArray::CreateVertexArray()
		{
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);
		}

		void VertexArray::AddBuffer(VertexBuffer& vb)
		{
			Bind();
			vb.Bind();

			glEnableVertexAttribArray(0);
		}
	}
}
