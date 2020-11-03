#pragma once

#include <stdio.h>
#include <sstream>
#include <fstream>

#include "../Manager/LogManager.h"

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
		};
	}

}

