#include "LogManager.h"

namespace Queen
{
	namespace Managers
	{

		//Log Names
		const const char* g_DEFAULT_LOGGER_NAME = "DEFAULT";
		const const char* g_LOG_LOGGER_NAME = "LOG MNGER";

		//GetLoggers
		#define DEFAULT_LOGGER LogManager::Get().GetLog(g_DEFAULT_LOGGER_NAME)
		#define LOG_LOGGER LogManager::Get().GetLog(g_LOG_LOGGER_NAME)

		//Create Message
		const const char* g_CREATE_LOG = "Log with name '{v}' has been created.";

		//Deleted Message
		const const char* g_DELETE_LOG = "{v} has been deleted.";

		//Error Message
		const const char* g_ERROR_LOG_ALREADY_STARTED = "Log Manager has already been started!";
		const const char* g_ERROR_LOG_NOT_STARTED = "Log Manager has not been started!";
		const const char* g_ERROR_LOG_DONT_EXIST = "Logger with name {v} do not exist!";
		const const char* g_ERROR_LOG_DUPLPICATE = "There is already a Logger with that name.";

		LogManager::LogManager()
		{
			
		}

		LogManager::~LogManager()
		{
			if (m_Running)
				LOG_LOGGER.LogMsg(System::Log::Level::TRACE, "Log Manager has been destroyed.");
		}

		void LogManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;
				this->CreateLog(g_DEFAULT_LOGGER_NAME);
				this->CreateLog(g_LOG_LOGGER_NAME);
				this->Log(System::Log::Level::TRACE, "Log Manager has been started.");
				this->Log(g_LOG_LOGGER_NAME, System::Log::Level::INFO, "Initialised.");
			}
			else
				this->Log(System::Log::Level::ERROR, g_ERROR_LOG_ALREADY_STARTED);
		}

		void LogManager::Shutdown()
		{
			if (m_Running)
			{
				m_Running = false;

				this->Log(System::Log::Level::INFO, "Log Manager is shutting down:");

				this->DeleteLog(g_LOG_LOGGER_NAME);

				this->Log(System::Log::Level::INFO, "Bye!");
				this->DeleteLog(g_DEFAULT_LOGGER_NAME);
			}
		}

		void LogManager::CreateLog(const char* name)
		{
			if (m_Running)
			{
				if (m_loggers.find(name) != m_loggers.end())
					this->Log(System::Log::Level::ERROR, g_ERROR_LOG_DUPLPICATE);
				else
				{
					System::Log l;
					l.setName(name);
					m_loggers[name] = l;

					this->LogParams(System::Log::Level::TRACE, g_CREATE_LOG, { name });
				}
			}
		}

		void LogManager::DeleteLog(const char* name)
		{
			if (m_Running)
			{
				this->Log(name, System::Log::Level::TRACE, "Deleting...");

				if (m_loggers.find(name) != m_loggers.end())
				{
					m_loggers.erase(name);
					this->LogParams(System::Log::Level::WARN, g_DELETE_LOG, { name });
				}
				else
					this->LogParams(System::Log::Level::ERROR, g_ERROR_LOG_DONT_EXIST, { name });
			}
		}

		void LogManager::Log(System::Log::Level l, const char* msg)
		{
			this->GetLog(g_DEFAULT_LOGGER_NAME).LogMsg(l, msg);
		}

		void LogManager::Log(const char* log_name, System::Log::Level l, const char* msg)
		{
			this->GetLog(log_name).LogMsg(l, msg);
		}

		void LogManager::LogParams(System::Log::Level l, const char* msg, std::initializer_list<const char*> li)
		{
			this->GetLog(g_DEFAULT_LOGGER_NAME).LogMsgParam(l, msg, li);
		}

		void LogManager::LogParams(const char* log_name, System::Log::Level l, const char* msg, std::initializer_list<const char*> li)
		{
			this->GetLog(log_name).LogMsgParam(l, msg, li);
		}
	}
}