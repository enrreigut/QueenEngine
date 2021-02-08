#pragma once

#include "glm/glm.hpp"
#include "../Renderer/Shader.h"

namespace Queen
{
	namespace Scenes
	{
		namespace Debug
		{
			struct Grid
			{
				int m_Width = 10;
				int m_Height = 10;
				int m_Resolution = 10;

				glm::vec3 m_Transform = glm::vec3(0.0f);

				unsigned int m_VaoId = 0;
				unsigned int m_VboId = 0;
				unsigned int m_IboId = 0;
				Queen::Renderer::Shader m_Shader;

				std::vector<glm::vec3> m_GridVertex;
				std::vector<glm::uvec4> m_GridIndeces;

				void CalculateGrid()
				{
					//Vertexes
					for (int j = 0; j <= m_Resolution; ++j) {
						for (int i = 0; i <= m_Resolution; ++i) {
							float x = (float)i * ((float)m_Width / (float)m_Resolution);
							float y = 0;
							float z = (float)j * ((float)m_Height / (float)m_Resolution);
							m_GridVertex.push_back(glm::vec3(x - ((float)m_Width / 2), y, z - ((float)m_Height / 2)));
						}
					}

					//Indexes
					for (int j = 0; j < m_Resolution; ++j) {
						for (int i = 0; i < m_Resolution; ++i) {

							int row1 = j * (m_Resolution + 1);
							int row2 = (j + 1) * (m_Resolution + 1);

							m_GridIndeces.push_back(glm::uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
							m_GridIndeces.push_back(glm::uvec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));

						}
					}
				}

				void CreateGrid()
				{
					m_Shader.LoadShaders("Resources/Shaders/Grid/VertexShader.vert", "Resources/Shaders/Grid/FragmentShader.frag");

					glGenVertexArrays(1, &m_VaoId);
					glBindVertexArray(m_VaoId);

					glGenBuffers(1, &m_VboId);
					glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
					glBufferData(GL_ARRAY_BUFFER, m_GridVertex.size() * sizeof(glm::vec3), &m_GridVertex[0], GL_STATIC_DRAW);

					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

					glGenBuffers(1, &m_IboId);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IboId);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_GridIndeces.size() * sizeof(glm::uvec4), &m_GridIndeces[0], GL_STATIC_DRAW);

					glBindVertexArray(0);

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
					glDisableVertexAttribArray(0);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
				}

				void UpdateGrid()
				{
					if (m_Width <= 0)
						m_Width = 1;

					if (m_Height <= 0)
						m_Height = 1;

					if (m_Resolution <= 0)
						m_Resolution = 1;

					m_GridVertex.clear();
					m_GridIndeces.clear();

					glDeleteVertexArrays(1, &m_VaoId);
					glDeleteBuffers(1, &m_IboId);
					glDeleteBuffers(1, &m_VboId);

					CalculateGrid();
					CreateGrid();
				}
			};
		}
	}
}