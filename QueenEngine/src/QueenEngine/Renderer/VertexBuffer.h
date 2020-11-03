#pragma once

#include "GL/glew.h"

namespace Queen
{
	namespace Renderer
	{
		class VertexBuffer
		{
		public:

			VertexBuffer();
			~VertexBuffer();

			bool Create(float* vertices, size_t& size);
			bool Bind();
			bool Unbind();

		private:

			GLuint m_VBO;
		};
	}
}


