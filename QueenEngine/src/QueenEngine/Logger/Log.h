#pragma once

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <string>
#include <initializer_list>

#include "../Manager/Manager.h"
#include "../Utils/Timer.h"

namespace Queen
{
	namespace System
	{

		struct LevelColorChannel
		{
			const char* WHITE;
			const char* YELLOW;
			const char* RED;
		};

		class Log
		{
		public:

			Log() {}
			~Log() {}

			enum class Level { TRACE = 0, INFO = 1, WARN = 2, ERROR = 3 };

			void setName(const char* name) { m_Name = name; }
			const char* getLevelRepresentation(Level& l);
			void LogMsg(Level l, const char* msg);

			void LogMsgParam(Level l, const char* msg, const std::initializer_list<const char*>& il);

		private:

			Utils::Timer m_T;
			const char* m_Name = "DEFAULT";
			LevelColorChannel m_ColorChannels = { "\x1B[97m" ,"\x1B[93m" ,"\x1B[91m" };
			const char* m_Color = m_ColorChannels.WHITE;
		};
	}
}