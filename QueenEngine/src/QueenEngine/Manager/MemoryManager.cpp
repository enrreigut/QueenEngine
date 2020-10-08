#include "MemoryManager.h"


const const char* g_DESTROY_MEM = "Memory Manager has been destroyed.";
const const char* g_START_MEM = "Memory Manager has started... Hello!";
const const char* g_SHUTDOWN_MEM = "Memory Manager is shutted down... Bye!";
const const char* g_ERROR_MEM_ALREADY_STARTED = "Memory Manager has already been started!";
const const char* g_ERROR_MEM_NOT_STARTED = "Memory Manager has not been started!";

namespace Queen
{
	namespace Managers
	{
		MemoryManager::MemoryManager()
		{
			
		}

		MemoryManager::~MemoryManager()
		{
			LogManager::Get().Log(System::Log::Level::TRACE, g_DESTROY_MEM);
		}

		void MemoryManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;

				LogManager::Get().Log(System::Log::Level::TRACE, g_START_MEM);
			}
			else
			{
				LogManager::Get().Log(System::Log::Level::ERROR, g_ERROR_MEM_ALREADY_STARTED);
			}
		}

		void MemoryManager::Shutdown()
		{
			if (!m_Running)
			{
				LogManager::Get().Log(System::Log::Level::ERROR, g_ERROR_MEM_NOT_STARTED);
			}
			else
			{
				LogManager::Get().Log(System::Log::Level::WARN, g_SHUTDOWN_MEM);

				m_Running = false;
			}
		}

	}
}