#pragma once

#include <vector>
#include "glm/glm.hpp"

#include "../Utils/FileReader.h"

namespace Queen
{
	namespace Entity
	{
		namespace Component
		{
			struct Component
			{

			};

			struct Model : public Component
			{
				Utils::FileReader m_Reader;

				std::vector<glm::vec3> m_Vertices;
				std::vector<glm::vec3> m_Normals;
				std::vector<glm::vec2> m_Uvs;
				std::vector<unsigned int> m_Indexes;

				const char* m_Name;

				void LoadObj(const char* filePath)
				{
					m_Reader.GetModelData(filePath, m_Vertices, m_Indexes, m_Uvs, m_Normals);
				}

			};

			struct Transform : public Component
			{
				glm::vec3 m_Transform;
			};

			struct Rotation : public Component
			{
				glm::vec3 m_Transform;
			};

			struct Scale : public Component
			{
				glm::vec3 m_Transform;
			};
		}
	}
}

