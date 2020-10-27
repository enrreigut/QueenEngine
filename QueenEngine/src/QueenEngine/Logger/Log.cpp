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
			case Log::Level::SUCCESS:
				m_Color = m_ColorChannels.GREEN;
				return "SUCCESS";
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
		
		void Log::GUILogMsg(Level l, GUI::Logger& logger, const char* msg)
		{
			logger.AddLog("[%s] %s(%s): %s\n", m_T.getDateAndTime(), m_Name, getLevelRepresentation(l), msg);
		}

		//Additional Functions for Logging Params
		//To be added in here: Link Erros due to templates
	}
}