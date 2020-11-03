#pragma once

#include <vector>
#include <GL/glew.h>

namespace Queen
{
	namespace Renderer
	{
		struct VertexBufferElement
		{
			unsigned int type;
			unsigned int count;
			bool normalized;

			static unsigned int GetSizeOfType(unsigned int type)
			{
				switch (type)
				{
				case GL_FLOAT:			return sizeof(GL_FLOAT);
				case GL_UNSIGNED_INT:	return sizeof(GL_UNSIGNED_INT);
				case GL_UNSIGNED_BYTE:	return sizeof(GL_UNSIGNED_BYTE);
				}

				return 0;
			}
		};

		class VertexBufferLayout
		{
		public:

			VertexBufferLayout()
			{
				m_Stride = 0;
			}

			template<typename T>
			void Push(unsigned int count)
			{
				static_assert(false);
			}
			
			template<>
			void Push<float>(unsigned int count)
			{
				m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
				m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
			}

			template<>
			void Push<unsigned int>(unsigned int count)
			{
				m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
				m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
			}

			template<>
			void Push<unsigned char>(unsigned int count)
			{
				m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
				m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
			}

			inline const std::vector<VertexBufferElement> GetElements() { return m_Elements; }
			inline unsigned int GetStride() const{ return m_Stride; }

		private:

			std::vector<VertexBufferElement> m_Elements;
			unsigned int m_Stride;
		};
	}
}


