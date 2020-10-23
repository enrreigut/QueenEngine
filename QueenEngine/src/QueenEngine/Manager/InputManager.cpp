#include "InputManager.h"

namespace Queen
{
	namespace Managers
	{
		void Window_Keyscan_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);

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

				m_Running = false;
			}
		}

		bool checkStatus(Input::KeyInput* keyInp, int key, int status)
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

		bool InputManager::IsKeyDown(int&& key)
		{
			return checkStatus(m_KeyInput, key, 1);
		}
		
		bool InputManager::IsKeyReleased(int&& key)
		{
			return checkStatus(m_KeyInput, key, 0);
		}

		bool InputManager::IsKeyPressed(int&& key)
		{
			return checkStatus(m_KeyInput, key, 2);
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

			QE_LOG_PARAMS(QE_TRACE, g_WIN_CALLBACK_KEYINPUT, key, TranslateAction(action));
		}
	}
}