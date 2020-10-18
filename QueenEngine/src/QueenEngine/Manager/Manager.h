#pragma once

#include "../Messages/Messages.h"

namespace Queen 
{
	namespace Managers
	{
		class Manager
		{
		public:

			virtual void Start() {}
			virtual void Shutdown() {}

		protected:

			Manager() {}
			~Manager() {}

			bool m_Running = false;
		};
	}
}
