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

			//Mouse

			bool IsMouseButtonDown(int&& mouseBut);
			bool IsMouseButtonUp(int&& mouseBut);
			bool IsMouseButtonPressed(int&& mouseBut);
			bool IsKeyPressed(GLFWwindow* win, int&& key);
		
			bool IsScrollUp();
			bool IsScrollDown();

			inline double GetMousePosX()& { return m_MouseInput->GetXPos(); }
			inline double GetMousePosY()& { return m_MouseInput->GetYPos(); }

			inline double GetMouseScrollY()& {return  m_MouseInput->GetYOffset(); }
			void ResetScrollY() { m_MouseInput->SetYOffset(0.0); }
			//Callbacks

			static void Window_Keyscan_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void Window_Mouse_Button_callback(GLFWwindow* window, int button, int action, int mods);
			static void Window_Mouse_Position_Callback(GLFWwindow* window, double xpos, double ypos);
			static void Window_Mouse_Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);

		public:

			bool p_DebugEvents = true;

		private:

			Input::KeyInput* m_KeyInput;
			Input::MouseInput* m_MouseInput;
		};
	}
}
