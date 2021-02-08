#pragma once

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#include "GL/glew.h"

namespace Queen
{
	namespace Renderer
	{
		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 normals;
			glm::vec2 uvs;
		};

		class VertexBuffer
		{
		public:

			VertexBuffer();
			~VertexBuffer();

			bool Create(std::vector<Vertex>& vertices);
			bool Bind();
			bool Unbind();

		private:

			GLuint m_VBO;
		};
	}
}


