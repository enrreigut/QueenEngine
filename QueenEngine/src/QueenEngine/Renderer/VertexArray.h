#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Queen
{
	namespace Renderer
	{
		class VertexArray
		{
		public:

			VertexArray();
			~VertexArray();

			void CreateVertexArray();

			inline const void Bind(){ glBindVertexArray(m_VAO); }
			inline const void Unbind(){ glBindVertexArray(0); }
			void AddBuffer(VertexBuffer& vb);

		private:		

			unsigned int m_VAO;

		};
	}
}


