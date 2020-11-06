#include "FileReader.h"

namespace Queen
{
	namespace Utils
	{

		void FileReader::GetFileContent(std::string& str, const char* filePath)
		{
			std::ifstream fileStream(filePath, std::ios::in);

			if (fileStream.is_open())
			{
				std::stringstream ss;
				ss << fileStream.rdbuf();
				str = ss.str();
				fileStream.close();
			}
			else
			{
				QE_LOG_PARAMS(QE_ERROR, "File: {v} could not be opened!", filePath);
			}
		}

		void FileReader::Refactor(std::vector<glm::vec3>& verts, std::vector<unsigned int>& indexes)
		{
			std::vector<glm::vec3> temp_verts = verts;
			verts.clear();

			for (int i = 0; i < indexes.size(); i++)
				verts.push_back(temp_verts.at(indexes.at(i)));

			temp_verts.clear();
		}
			
		bool FileReader::GetModelData(const char* filePath, std::vector<glm::vec3>& verts, std::vector<unsigned int>& indexes, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals)
		{
			std::ifstream myFile(filePath);
			std::string line;

			if (!myFile.is_open())
			{
				std::string error = "Error reading the following file: ";
				return false;
			}
			else
			{
				std::vector<std::string> splittedLine;
				std::vector<std::string> facesLine;

				while (std::getline(myFile, line))
				{
					split(&splittedLine, &line, ' ');

					if (splittedLine.at(0) == "v")
					{
						glm::vec3 v(std::stof(splittedLine.at(1)), std::stof(splittedLine.at(2)), std::stof(splittedLine.at(3)));
						verts.push_back(v);
					}
					else if (splittedLine.at(0) == "vt")
					{
						glm::vec2 v(std::stof(splittedLine.at(1)), std::stof(splittedLine.at(2)));
						uvs.push_back(v);
					}
					else if (splittedLine.at(0) == "f")
					{
						split(&facesLine, &splittedLine.at(1), '/');
						indexes.push_back(std::stoi(facesLine.at(0)) - 1);
						facesLine.clear();

						split(&facesLine, &splittedLine.at(2), '/');
						indexes.push_back(std::stoi(facesLine.at(0)) - 1);
						facesLine.clear();

						split(&facesLine, &splittedLine.at(3), '/');
						indexes.push_back(std::stoi(facesLine.at(0)) - 1);
						facesLine.clear();
					}

					splittedLine.clear();
				}

				myFile.close();
				return true;
			}
		}
	}
}