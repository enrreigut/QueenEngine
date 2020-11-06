#pragma once

#include <vector>

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

			bool Create(std::vector<unsigned int>& indices);
			bool Bind();
			bool Unbind();

		private:

			GLuint m_IBO;
		};
	}
}


