#include "EventManager.h"

namespace Queen
{
	namespace Managers
	{
		EventManager::EventManager()
		{

		}
		EventManager::~EventManager()
		{
			QE_LOG(QE_TRACE, g_EVENT_MAN_INFO_DESTROYED);
		}

		void EventManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;

				QE_LOG(QE_TRACE, g_EVENT_MAN_INFO_START);
			}
			else
			{
				QE_LOG(QE_TRACE, g_EVENT_MAN_ERROR_ALREADY_STARTED);
			}
		}

		void EventManager::Shutdown()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_EVENT_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				QE_LOG(QE_WARN, g_EVENT_MAN_INFO_SHUTDOWN);

				m_Running = false;
			}
		}
	}
}