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
			inline int GetMouseStatus()& { return m_MouseStatus; }
			inline double GetXPos()& { return m_xPos; }
			inline double GetYPos()& { return m_yPos; }
			inline double GetXOffset() { return m_xOffset; }
			inline double GetYOffset() { return m_yOffset; }
			inline bool IsMouseMoving()& { return m_MouseMove; }

			void SetMouseButton(int& mouseButton) { m_MouseButton = mouseButton; }
			void SetMouseStatus(int& mouseStatus) { m_MouseStatus = mouseStatus; }
			void SetXPos(double& xpos) { m_xPos = xpos; }
			void SetYPos(double& ypos) { m_yPos = ypos; }
			void SetXOffset(double& xOffset) { m_xOffset = xOffset; }
			void SetXOffset(double&& xOffset) { m_xOffset = xOffset; }
			void SetYOffset(double& yOffset) { m_yOffset = yOffset; }
			void SetYOffset(double&& yOffset) { m_yOffset = yOffset; }
			void SetIsMoving(bool& mov) { m_MouseMove = mov; }

		private:
			
			int m_MouseButton = 0;
			int m_MouseStatus = 0;

			double m_xPos = 0.0;
			double m_yPos = 0.0;

			double m_xOffset = 0.0;
			double m_yOffset = 0.0;

			bool m_MouseMove = false;
		};
	}
}


