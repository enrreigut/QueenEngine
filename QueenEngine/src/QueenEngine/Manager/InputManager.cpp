#include "InputManager.h"

namespace Queen
{
	namespace Managers
	{
		InputManager::InputManager()
		{

		}
		InputManager::~InputManager()
		{
			QE_LOG(QE_TRACE, g_INPUT_MAN_INFO_DESTROYED);
		}

		void InputManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;

				m_KeyInput = new Input::KeyInput;
				m_MouseInput = new Input::MouseInput;

				QE_LOG(QE_TRACE, g_INPUT_MAN_INFO_START);
			}
			else
			{
				QE_LOG(QE_TRACE, g_INPUT_MAN_ERROR_ALREADY_STARTED);
			}
		}

		void InputManager::Shutdown()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_INPUT_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				QE_LOG(QE_WARN, g_INPUT_MAN_INFO_SHUTDOWN);

				delete m_KeyInput;
				delete m_MouseInput;

				m_Running = false;
			}
		}

		bool checkStatusKey(Input::KeyInput* keyInp, int key, int status)
		{
			if (keyInp->GetKeycode() == key)
			{
				if (keyInp->GetStatus() == status)
					return true;
				else
					return false;
			}
			return false;
		}

		bool checkStatusMouse(Input::MouseInput* mouseInp, int button, int status)
		{
			if (mouseInp->GetMouseButton() == button)
			{
				if (mouseInp->GetMouseStatus() == status)
					return true;
				else
					return false;
			}
			return false;
		}

		bool InputManager::IsKeyDown(int&& key)
		{
			return checkStatusKey(m_KeyInput, key, 1);
		}
		
		bool InputManager::IsKeyReleased(int&& key)
		{
			return checkStatusKey(m_KeyInput, key, 0);
		}

		bool InputManager::IsKeyPressed(int&& key)
		{
			return checkStatusKey(m_KeyInput, key, 2);
		}

		bool InputManager::IsKeyPressed(GLFWwindow* win, int&& key)
		{
			return glfwGetKey(win, key) == GLFW_PRESS;
		}

		// Mouse
		bool InputManager::IsMouseButtonDown(int&& mouseBut)
		{
			return checkStatusMouse(m_MouseInput, mouseBut, 1);
		}

		bool InputManager::IsMouseButtonUp(int&& mouseBut)
		{
			return checkStatusMouse(m_MouseInput, mouseBut, 0);
		}

		bool InputManager::IsMouseButtonPressed(int&& mouseBut)
		{
			return checkStatusMouse(m_MouseInput, mouseBut, 2);
		}

		bool InputManager::IsScrollUp()
		{
			if (m_MouseInput->GetYOffset() > 0.0f)
				return true;
			else
				return false;
		}

		bool InputManager::IsScrollDown()
		{
			if (m_MouseInput->GetYOffset() < 0.0f)
				return true;
			else
				return false;
		}

		const char* TranslateAction(int& action)
		{
			switch (action)
			{
			case 1:
				return "DOWN";
			case 2:
				return "PRESSED";
				break;
			default:
				return "RELEASED";
			}
		}

		void InputManager::Window_Keyscan_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			InputManager::Get().m_KeyInput->SetKeycode(key);
			InputManager::Get().m_KeyInput->SetStatus(action);

			if(InputManager::Get().p_DebugEvents)
				QE_LOG_PARAMS(QE_TRACE, g_WIN_CALLBACK_KEYINPUT, key, TranslateAction(action));
		}

		void InputManager::Window_Mouse_Button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			InputManager::Get().m_MouseInput->SetMouseButton(button);
			InputManager::Get().m_MouseInput->SetMouseStatus(action);
	
			if (InputManager::Get().p_DebugEvents)
				QE_LOG_PARAMS(QE_TRACE, "Mouse Button {v} is {v}", button, TranslateAction(action));
		}

		void InputManager::Window_Mouse_Position_Callback(GLFWwindow* window, double xpos, double ypos)
		{
			InputManager::Get().m_MouseInput->SetXPos(xpos);
			InputManager::Get().m_MouseInput->SetYPos(ypos);

			if (InputManager::Get().p_DebugEvents)
				QE_LOG_PARAMS(QE_TRACE, "Mouse Pos: ({v}, {v})", xpos, ypos);
		}

		void InputManager::Window_Mouse_Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
		{
			InputManager::Get().m_MouseInput->SetXOffset(xoffset);
			InputManager::Get().m_MouseInput->SetYOffset(yoffset);

			if (InputManager::Get().p_DebugEvents)
				QE_LOG_PARAMS(QE_TRACE, "Mouse Scroll: ({v}, {v})", xoffset, yoffset);
		}
	}
}