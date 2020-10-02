#pragma once

#include <unordered_map>

#include "Manager.h"
#include "../Utils/Singleton.h"
#include "../Logger/Log.h"

namespace Queen
{
	namespace Managers
	{

		class LogManager : public Manager, public Utils::Singleton<LogManager>
		{

			friend class Utils::Singleton<LogManager>;

		public:

			void Start() override;
			void Shutdown() override;
			
			inline System::Log GetLog(const char* name) { return m_loggers[name]; }

			void CreateLog(const char* name);
			void DeleteLog(const char* name);

			void Log(System::Log::Level l, const char* msg);
			void Log(const char* log_name, System::Log::Level l, const char* msg);
			void LogParams(System::Log::Level l, const char* msg, std::initializer_list<const char*> li);
			void LogParams(const char* log_name, System::Log::Level l, const char* msg, std::initializer_list<const char*> li);

		private:

			LogManager();
			~LogManager();

			std::unordered_map<const char*, System::Log> m_loggers;
		};

	}

}
