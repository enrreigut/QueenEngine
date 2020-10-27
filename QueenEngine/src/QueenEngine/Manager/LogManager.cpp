#include "LogManager.h"

namespace Queen
{
	namespace Managers
	{

		//Log Default name,
		const const char* g_DEFAULT_LOGGER_NAME = "DEFAULT";

		//Get Default Logger and making it a define for cleaner code
		#define DEFAULT_LOGGER LogManager::Get().GetLog(g_DEFAULT_LOGGER_NAME)
		
		LogManager::LogManager()
		{
			
		}

		LogManager::~LogManager()
		{
		}

		/*Mainly print a msg of start if Manager can start. If it was already started Logger outputs an error*/
		void LogManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;
				
				if(this->CreateLog(g_DEFAULT_LOGGER_NAME))
					QE_LOG(QE_TRACE, g_LOG_MAN_INFO_START);
			}
			else
				QE_LOG(QE_ERROR, g_LOG_MAN_ERROR_ALREADY_STARTED);
		}

		/*Shutdown the manager if it is running. If not return an error msg.*/
		void LogManager::Shutdown()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_LOG_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				QE_LOG(QE_WARN, g_LOG_MAN_INFO_SHUTDOWN);
				
				/*Because we can create more than one Logger we need to delete all of them if Logger Manager is shutted down.
				We could leave it to the destructor, however, bacause we can shutdown the LoggerManager but the application running we need to handle
				this ourselves.
				*/
				std::vector<const char*> keys;
				for (auto it = m_loggers.begin(); it != m_loggers.end(); ++it)
					keys.push_back(it->first);

				for (auto name : keys)
				{
					if (!this->DeleteLog(name))
					{
						if (!this->ExistsLog(g_DEFAULT_LOGGER_NAME))
							this->CreateLog(g_DEFAULT_LOGGER_NAME);

						QE_LOG_PARAMS(QE_ERROR, "Error deleting logger: {v}", name);
						
						break;
					}
				}

				m_Running = false;
			}
		}

		/*Create a Logger. If there is already a Logger with than name it return false with an error msg.*/
		bool LogManager::CreateLog(const char* name)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_LOG_MAN_ERROR_NOT_STARTED);
				return false;
			}
			else
			{
				if (m_loggers.find(name) != m_loggers.end())
				{
					QE_LOG(QE_ERROR, g_LOG_MAN_ERROR_DUPLPICATE);
					return false;
				}
				else
				{
					System::Log l;
					l.setName(name);
					m_loggers[name] = l;

					QE_LOG_PARAMS(QE_TRACE, g_LOG_MAN_INFO_CREATE, name);
					return true;
				}
			}
		}

		/*Deletes a Logger. If the Logger do not exists, returns false with an error msg*/
		bool LogManager::DeleteLog(const char* name)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_LOG_MAN_ERROR_NOT_STARTED);
				return false;
			}
			else
			{
				if (m_loggers.find(name) != m_loggers.end())
				{
					QE_LOG_PARAMS(QE_TRACE, g_LOG_MAN_INFO_DELETE, name);
					m_loggers.erase(name);
					return true;
				}
				else
				{
					QE_LOG_PARAMS(QE_ERROR, g_LOG_MAN_ERROR_DONT_EXIST, name);
					return false;
				}
			}
		}

		/*All Logging option. Pretty straight forward code, just call the Loggers LogMsg methods.*/
		void LogManager::Log(System::Log::Level l, const char* msg)
		{
			if(m_Running && ExistsLog(g_DEFAULT_LOGGER_NAME))
				this->GetLog(g_DEFAULT_LOGGER_NAME).LogMsg(l, msg);
		}

		void LogManager::Log(const char* log_name, System::Log::Level l, const char* msg)
		{
			if (m_Running && ExistsLog(log_name))
				this->GetLog(log_name).LogMsg(l, msg);
		}

		void LogManager::LogGUI(System::Log::Level l, GUI::Logger& logger, const char* msg)
		{
			if (m_Running && ExistsLog(g_DEFAULT_LOGGER_NAME))
				this->GetLog(g_DEFAULT_LOGGER_NAME).GUILogMsg(l, logger, msg);
		}
	}
}