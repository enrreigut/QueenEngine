#pragma once

namespace Queen
{
	namespace Entity
	{
		class BaseEnity
		{
		public:
			
			BaseEnity();
			~BaseEnity();

			virtual void OnInput() = 0;
			virtual void OnUpdate() = 0;
			virtual void OnDestroy() = 0;

		private:

			const char* m_Name  = "Default";

		};
	}
}


