#pragma once

#include <vector>
#include "glm/vec3.hpp"

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

			bool Create(std::vector<glm::vec3> & vertices);
			bool Bind();
			bool Unbind();

		private:

			GLuint m_VBO;
		};
	}
}


