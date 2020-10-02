#include "MemoryManager.h"

#define MEM_LOG_MANAGER_NAME "MEM MNGER"
#define MEM_LOGGER LogManager::Get().GetLog(MEM_LOG_MANAGER_NAME)

namespace Queen
{
	namespace Managers
	{
		MemoryManager::MemoryManager()
		{
			LogManager::Get().CreateLog(MEM_LOG_MANAGER_NAME);
		}

		MemoryManager::~MemoryManager()
		{
			if (m_Running)
				MEM_LOGGER.LogMsg(System::Log::Level::TRACE, "Memory Manager has been destroyed.");
		}

		void MemoryManager::Start()
		{
			m_Running = true;
			MEM_LOGGER.LogMsg(System::Log::Level::TRACE, "Memory Manager has been started.");
		}

		void MemoryManager::Shutdown()
		{
			m_Running = false;
			MEM_LOGGER.LogMsg(System::Log::Level::TRACE, "Memory Manager has been shutted down.");
		}

	}
}