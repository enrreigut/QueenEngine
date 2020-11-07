#pragma once

#include <vector>

#include "../Utils/FileReader.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

namespace Queen
{
	namespace Entity
	{
		namespace Component
		{
			struct Model
			{
				Utils::FileReader m_Reader;

				std::vector<glm::vec3> m_Vertices;
				std::vector<unsigned int> m_Indexes;
				std::vector<glm::vec2> m_Uvs;
				std::vector<glm::vec3> m_Normals;
				
				void LoadObj(const char* filePath)
				{
					m_Reader.GetModelData(filePath, m_Vertices, m_Indexes, m_Uvs, m_Normals);
					//m_Reader.Refactor(m_Vertices, m_Indexes);
				}
			};
		}
	}
}