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

	}
}