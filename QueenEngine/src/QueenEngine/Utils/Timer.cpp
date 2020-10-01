#include "Timer.h"

Timer::Timer()
{
	Update();	
}

Timer::~Timer()
{

}

void Timer::Update()
{
	time(&m_TimeDate);
	localtime_s(&m_TimeInfo, &m_TimeDate);
	strftime(m_TimeDate_s, 20, "%F %T", &m_TimeInfo);
}