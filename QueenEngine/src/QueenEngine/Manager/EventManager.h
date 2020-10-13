#pragma once

#include "../Utils/Singleton.h"

#include "Manager.h"

#include "LogManager.h"

namespace Queen
{
	namespace Managers
	{
		class EventManager : public Manager, public Utils::Singleton<EventManager>
		{
			friend class Singleton<EventManager>;

		public:

			EventManager();
			~EventManager();

			void Start() override;
			void Shutdown() override;

		private:



		};
	}
}


