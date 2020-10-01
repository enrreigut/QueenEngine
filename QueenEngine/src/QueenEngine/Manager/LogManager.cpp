#include "LogManager.h"

namespace Queen
{
	namespace Managers
	{

		LogManager::LogManager()
		{

		}

		LogManager::~LogManager()
		{
			if (m_Running)
				m_logger.LogMsg(System::Log::Level::TRACE, "Log Manager has been destroyed.");
		}

		void LogManager::Start()
		{
			m_Running = true;
			m_logger.LogMsg(System::Log::Level::TRACE, "Log Manager has been started.");
		}

		void LogManager::Shutdown()
		{
			m_Running = false;
			m_logger.LogMsg(System::Log::Level::TRACE, "Log Manager has been shutted down.");
		}

		void LogManager::CreateLog(const char* name)
		{
			if (m_Running)
			{
				if (m_loggers.find(name) != m_loggers.end())
					m_logger.LogMsg(System::Log::Level::ERROR, "There is already a Logger with that name.");
				else
				{
					System::Log l;
					l.setName(name);
					m_loggers[name] = l;

					m_logger.LogMsgParam(System::Log::Level::TRACE, "Log with name '{v}' has been created.", { name });
				}
			}
		}
	}
}