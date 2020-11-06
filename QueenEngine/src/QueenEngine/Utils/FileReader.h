#pragma once

#include <stdio.h>
#include <sstream>
#include <fstream>

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#include "../Manager/LogManager.h"
#include "../Utils/StringUtils.h"

namespace Queen
{
	namespace Utils
	{

		class FileReader
		{
		public:

			FileReader() {}
			~FileReader() {}
	
			void GetFileContent(std::string& str, const char* filePath);
			bool GetModelData(const char* filePath, std::vector<glm::vec3>& verts, std::vector<unsigned int>& indexes, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals);
			void Refactor(std::vector<glm::vec3>& verts, std::vector<unsigned int>& indexes);
		};
	}

}

