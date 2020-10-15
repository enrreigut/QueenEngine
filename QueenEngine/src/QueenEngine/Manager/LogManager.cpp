#include "LogManager.h"

/*Log Messages for Logger Manager and some general stuff*/
const const char* g_CREATE = "Logger with name '{v}' has been created.";
const const char* g_DELETE = "{v} has been deleted.";
const const char* g_ERROR_DONT_EXIST = "Logger with name {v} do not exist!";
const const char* g_ERROR_DUPLPICATE = "There is already a Logger with that name.";

const const char* g_DESTROY_LOG = "Log Manager has been destroyed.";
const const char* g_START_LOG = "Log Manager has started... Hello!";
const const char* g_SHUTDOWN_LOG = "Log Manager is shutted down... Bye!";
const const char* g_ERROR_LOG_ALREADY_STARTED = "Log Manager has already been started!";
const const char* g_ERROR_LOG_NOT_STARTED = "Log Manager has not been started!";

namespace Queen
{
	namespace Managers
	{

		//Log Default name,
		const const char* g_DEFAULT_LOGGER_NAME = "DEFAULT";

		//Get Default Logger and making it a define for cleare code
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
					this->Log(System::Log::Level::TRACE, g_START_LOG);
			}
			else
				this->Log(System::Log::Level::ERROR, g_ERROR_LOG_ALREADY_STARTED);
		}

		/*Shutdown the manager if it is running. If not return an error msg.*/
		void LogManager::Shutdown()
		{
			if (!m_Running)
			{
				this->Log(System::Log::Level::ERROR, g_ERROR_LOG_NOT_STARTED);
			}
			else
			{
				this->Log(System::Log::Level::WARN, g_SHUTDOWN_LOG);
				
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
						this->LogParams(System::Log::Level::ERROR, "Error deleting logger: {v}", name);
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
				this->Log(System::Log::Level::ERROR, g_ERROR_LOG_NOT_STARTED);
				return false;
			}
			else
			{
				if (m_loggers.find(name) != m_loggers.end())
				{
					this->Log(System::Log::Level::ERROR, g_ERROR_DUPLPICATE);
					return false;
				}
				else
				{
					System::Log l;
					l.setName(name);
					m_loggers[name] = l;

					this->LogParams(System::Log::Level::TRACE, g_CREATE, name);
					return true;
				}
			}
		}

		/*Deletes a Logger. If the Logger do not exists, returns false with an error msg*/
		bool LogManager::DeleteLog(const char* name)
		{
			if (!m_Running)
			{
				this->Log(System::Log::Level::ERROR, g_ERROR_LOG_NOT_STARTED);
				return false;
			}
			else
			{
				if (m_loggers.find(name) != m_loggers.end())
				{
					this->LogParams(System::Log::Level::TRACE, g_DELETE, name);
					m_loggers.erase(name);
					return true;
				}
				else
				{
					this->LogParams(System::Log::Level::ERROR, g_ERROR_DONT_EXIST, name);
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
	}
}