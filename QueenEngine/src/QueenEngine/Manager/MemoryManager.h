#pragma once

#include <vector>

#include "../Utils/Singleton.h"

#include "Manager.h"
#include "LogManager.h"

namespace Queen
{
	namespace Managers
	{
		class MemoryManager : public Manager, public Utils::Singleton<MemoryManager>
		{
			friend class Singleton<MemoryManager>;

		public:

			void Start() override;
			void Shutdown() override;

		private:

			MemoryManager();
			~MemoryManager();
		};
	}
}

