#pragma once

#include <GLFW/glfw3.h>

namespace Queen
{
	namespace Input
	{
		class KeyInput
		{
		public:

			KeyInput();
			~KeyInput();

			inline int GetKeycode()& { return m_Keycode; }
			inline int GetStatus()& { return m_Status; }

			inline void SetKeycode(int keycode) { m_Keycode = keycode; }
			inline void SetStatus(int status) { m_Status = status; }
			
		private:

			int m_Keycode = 0;
			int m_Status  = 0;
		};
	}
}


