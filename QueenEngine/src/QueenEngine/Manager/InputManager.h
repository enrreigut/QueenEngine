#pragma once

#include <GLFW/glfw3.h>

#include "../Utils/Singleton.h"

#include "Manager.h"
#include "LogManager.h"

#include "../Inputs/keyInput.h"
#include "../Inputs/MouseInput.h"

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

			//Moouse

			bool IsMouseButtonDown(int&& mouseBut);
			bool IsMouseButtonUp(int&& mouseBut);
			bool IsMouseButtonPressed(int&& mouseBut);

			//Callbacks

			static void Window_Keyscan_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void Window_Mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		private:

			Input::KeyInput* m_KeyInput;
			Input::MouseInput* m_MouseInput;
		};
	}
}
