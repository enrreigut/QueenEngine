#pragma once

#include <unordered_map>

#include "Manager.h"
#include "../Utils/Singleton.h"
#include "../Logger/Log.h"

namespace Queen
{
	namespace Managers
	{
		/*Class which manages the Loggers (Log Objects). This is a Singleton thus only one can be created and handles all the logging and loggers.
		The picked strategy is to have a default Logger which Logs mostly everything but you are free to create more loggers to handle things independently.
		*/
		class LogManager : public Manager, public Utils::Singleton<LogManager>
		{

			friend class Utils::Singleton<LogManager>;

		public:
			/*Derived methods from base class Manager*/
			void Start() override;
			void Shutdown() override;
			
			/*Retrieve the desied Logger*/
			inline System::Log GetLog(const char* name)& { return m_loggers[name]; }
			/*Checks if manager is Running*/
			inline bool isRunning()& { return m_Running; }
			
			/*Create, Delete and See if a Log has been created*/
			bool CreateLog(const char* name);
			bool DeleteLog(const char* name);
			inline bool ExistsLog(const char* name) { return m_loggers.find(name) != m_loggers.end(); }

			/*Log making us of desired or default Log*/
			void Log(System::Log::Level l, const char* msg);
			void Log(const char* log_name, System::Log::Level l, const char* msg);

			template<typename... Args>
			void LogParams(System::Log::Level l, const char* msg, Args&&... li)
			{
				if (m_Running && ExistsLog("DEFAULT"))
					this->GetLog("DEFAULT").LogMsgParam(l, msg, li...);
			}
			
			template<typename... Args>
			void LogParams(const char* log_name, System::Log::Level l, const char* msg, Args&&... li)
			{
				if (m_Running && ExistsLog(log_name))
					this->GetLog(log_name).LogMsgParam(l, msg, li);
			}

		private:

			LogManager();
			~LogManager();

			std::unordered_map<const char*, System::Log> m_loggers;
		};

	}

}
