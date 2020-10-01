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

			void CreateLog(const char* name);
			inline System::Log GetLog(const char* name) { return m_loggers[name]; }

		private:

			LogManager();
			~LogManager();

			System::Log m_logger;
			std::unordered_map<const char*, System::Log> m_loggers;
		};

	}

}
