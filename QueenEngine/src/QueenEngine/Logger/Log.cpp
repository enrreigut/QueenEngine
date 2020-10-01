#include "Log.h"

const char* Log::getLevelRepresentation(Level &l)
{
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
	printf("%s[%s] %s(%s): %s\033[0m\n", m_Color, m_T.getDateAndTime(), m_Name, getLevelRepresentation(l), msg);
}

//TODO: ADD Support for differente types not only string representation
void Log::LogMsgParam(Level l, const char* msg, const std::initializer_list<const char*>& il)
{
	//Msg example:
	// Hola soy el Keke {v} y me gusta el {v}
	//Call to function would be:
	//LogMsgParam(Log::Level::INFO, "Hola soy el Keke {v} y me gusta el {v}", "Reina", "Betis");
	
	std::string s = msg;
	size_t pos = 0;

	for (auto elem : il)
	{
		pos = s.find("{v}");

		if (pos == std::string::npos)
			break;

		s.replace(pos, 3, elem);
	}

	printf("%s[%s] %s(%s): %s\033[0m\n", m_Color, m_T.getDateAndTime(), m_Name, getLevelRepresentation(l), s.c_str());
}