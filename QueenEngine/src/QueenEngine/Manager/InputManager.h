#pragma once

#include <GLFW/glfw3.h>

#include "../Utils/Singleton.h"

#include "Manager.h"
#include "LogManager.h"

#include "../Inputs/keyInput.h"

namespace Queen
{
	namespace Managers
	{

		class InputManager : public Manager, public Utils::Singleton<InputManager>
		{
			friend class Singleton<InputManager>;

		public:

			InputManager();
			~InputManager();

			void Start() override;
			void Shutdown() override;

			//Keys

			bool IsKeyDown(int&& key);
			bool IsKeyReleased(int&& key);
			bool IsKeyPressed(int&& key);

			static void Window_Keyscan_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		private:

			Input::KeyInput* m_KeyInput;
		};
	}
}
