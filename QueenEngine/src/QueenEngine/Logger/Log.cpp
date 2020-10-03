#include "Log.h"

/*Read Log.h file to know what each function does. Here will be some explanation of certains part of the code.*/

namespace Queen
{
	namespace System
	{

		const char* Log::getLevelRepresentation(Level& l)
		{
			/*Basic Switch to pick right colot*/

			switch (l)
			{
			case Log::Level::INFO:
				m_Color = m_ColorChannels.WHITE;
				return "INFO";
			case Log::Level::WARN:
				m_Color = m_ColorChannels.YELLOW;
				return "WARN";
			case Log::Level::ERROR:
				m_Color = m_ColorChannels.RED;
				return "ERROR";
			default:
				m_Color = m_ColorChannels.WHITE;
				return "TRACE";
			}
		}

		void Log::LogMsg(Level l, const char* msg)
		{
			/*Log output pattern
			eg: [YYYY-MM-DD HH:mm:ss] Name(Level): Message
			*/
			printf("%s[%s] %s(%s): %s\033[0m\n", m_Color, m_T.getDateAndTime(), m_Name, getLevelRepresentation(l), msg);
		}

		//TODO: ADD Support for differente types not only string representation
		void Log::LogMsgParam(Level l, const char* msg, const std::initializer_list<const char*>& il)
		{
			std::string s = msg;
			size_t pos = 0;

			/*for to replace the {v} with the correct parameters*/
			for (auto elem : il)
			{
				pos = s.find("{v}");

				if (pos == std::string::npos)
					break;

				s.replace(pos, 3, elem);
			}

			printf("%s[%s] %s(%s): %s\033[0m\n", m_Color, m_T.getDateAndTime(), m_Name, getLevelRepresentation(l), s.c_str());
		}
	}
}