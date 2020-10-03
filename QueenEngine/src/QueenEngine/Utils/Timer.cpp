#include "Timer.h"

/*Read Timer.h file to know what each function does. Here will be some explanation of certains part of the code.*/

namespace Queen
{
	namespace Utils
	{

		Timer::Timer()
		{
			Update();
		}

		Timer::~Timer()
		{

		}

		void Timer::Update()
		{
			//Get time in milliseconds since 1900 i believe
			time(&m_TimeDate);
			//Formats to a localtime struct
			localtime_s(&m_TimeInfo, &m_TimeDate);
			//Show desired format of localtime. The desired one is YYYY-MM-DD HH:mm:ss
			strftime(m_TimeDate_s, 20, "%F %T", &m_TimeInfo);
		}

	}
}
