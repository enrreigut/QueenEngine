#include "MemoryManager.h"

namespace Queen
{
	namespace Managers
	{
		MemoryManager::MemoryManager()
		{
			
		}

		MemoryManager::~MemoryManager()
		{
			QE_LOG(QE_TRACE, g_MEM_MAN_INFO_DESTROYED);
		}

		void MemoryManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;

				QE_LOG(QE_TRACE, g_MEM_MAN_INFO_START);
			}
			else
			{
				QE_LOG(QE_ERROR, g_MEM_MAN_ERROR_ALREADY_STARTED);
			}
		}

		void MemoryManager::Shutdown()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_MEM_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				QE_LOG(QE_WARN, g_MEM_MAN_INFO_SHUTDOWN);

				m_Running = false;
			}
		}
	}
}