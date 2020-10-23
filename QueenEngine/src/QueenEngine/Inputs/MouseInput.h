#pragma once


namespace Queen
{
	namespace Input
	{
		class MouseInput
		{
		public:

			MouseInput();
			~MouseInput();

			inline int GetMouseButton()& { return m_MouseButton; }
			inline int GetMuseStatus()& { return m_MouseStatus; }
			inline double GetXPos()& { return m_xPos; }
			inline double GetYPos()& { return m_yPos; }
			inline bool IsMouseMoving()& { return m_MouseMove; }

			void SetMouseButton(int& mouseButton) { m_MouseButton = mouseButton; }
			void SetMouseStatus(int& mouseStatus) { m_MouseStatus = mouseStatus; }
			void SetXPos(double& xpos) { m_xPos = xpos; }
			void SetYPos(double& ypos) { m_yPos = ypos; }
			void SetIsMoving(bool& mov) { m_MouseMove = mov; }

		private:
			
			int m_MouseButton;
			int m_MouseStatus;

			double m_xPos;
			double m_yPos;

			bool m_MouseMove;
		};
	}
}


