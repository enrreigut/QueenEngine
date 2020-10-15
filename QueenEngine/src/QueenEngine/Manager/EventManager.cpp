#include "EventManager.h"

const const char* g_DESTROY_EVENT = "Event Manager has been destroyed.";
const const char* g_START_EVENT = "Event Manager has started... Hello!";
const const char* g_SHUTDOWN_EVENT = "Event Manager is shutted down... Bye!";
const const char* g_ERROR_EVENT_ALREADY_STARTED = "Event Manager has already been started!";
const const char* g_ERROR_EVENT_NOT_STARTED = "Event Manager has not been started!";

namespace Queen
{
	namespace Managers
	{
		EventManager::EventManager()
		{

		}
		EventManager::~EventManager()
		{
			LogManager::Get().Log(System::Log::Level::TRACE, g_DESTROY_EVENT);
		}

		void EventManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;

				LogManager::Get().Log(System::Log::Level::TRACE, g_START_EVENT);
			}
			else
			{
				LogManager::Get().Log(System::Log::Level::ERROR, g_ERROR_EVENT_NOT_STARTED);
			}
		}

		void EventManager::Shutdown()
		{
			if (!m_Running)
			{
				LogManager::Get().Log(System::Log::Level::ERROR, g_ERROR_EVENT_NOT_STARTED);
			}
			else
			{
				LogManager::Get().Log(System::Log::Level::WARN, g_SHUTDOWN_EVENT);

				m_Running = false;
			}
		}
	}
}