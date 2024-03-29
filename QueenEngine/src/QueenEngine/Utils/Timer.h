#pragma once

#include <ctime>

#include "StringUtils.h"

class Timer
{
public:

	Timer();
	~Timer();

	void Update();

	auto& getDateAndTime() { Update();  return m_TimeDate_s; }
		
private:

	struct tm m_TimeInfo;
	time_t m_TimeDate;
	char m_TimeDate_s[20];
};

