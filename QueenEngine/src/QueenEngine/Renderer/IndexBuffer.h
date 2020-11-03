#pragma once

#include "GL/glew.h"

namespace Queen
{
	namespace Renderer
	{
		class IndexBuffer
		{
		public:

			IndexBuffer();
			~IndexBuffer();

			bool Create(unsigned int* indices, size_t& size);
			bool Bind();
			bool Unbind();

		private:

			GLuint m_IBO;
		};
	}
}


