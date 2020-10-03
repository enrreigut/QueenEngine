#pragma once

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <string>
#include <initializer_list>

#include "../Manager/Manager.h"
#include "../Utils/Timer.h"

/*
This file is the Log header which is just an interface for the class which handles the Log console outputing with an established format.
*/

namespace Queen
{
	namespace System
	{
		/*Console color output strucutre. Could be joined inside Log class but it does not aaffect and maybe is clear this way.*/
		struct LevelColorChannel
		{
			const char* WHITE;
			const char* YELLOW;
			const char* RED;
		};

		class Log
		{
		public:

			Log() {}
			~Log() {}

			/*Levels of the Logger*/
			enum class Level { TRACE = 0, INFO = 1, WARN = 2, ERROR = 3 };

			/*Set name for the Logger in other to identify them if more than one is created. For Logger Management go to Manager/LogManager.cpp/h */
			void setName(const char* name) { m_Name = name; }

			/*This is used to set the color in which text will be outputed according to its Level*/
			const char* getLevelRepresentation(Level& l);

			/*Method for outputing to console. We pass the desired level and the message*/
			void LogMsg(Level l, const char* msg);

			/*Method for outputing to console with parameters if wanted.
			The parameters are custom added and for now just supports only string parameters.
			Way of usage:
			"Hello my name is {v}"and {v} is where the parameter would be displayed
			*/
			void LogMsgParam(Level l, const char* msg, const std::initializer_list<const char*>& il);

		private:

			/*To establish moment of Log*/
			Utils::Timer m_T;

			/*Default name if one is not established*/
			const char* m_Name = "DEFAULT";

			/*Colors of output in ANSI depending on the level. The colors are BRIGHT WHITE, YELLOW AND RED
			97m = BRIGHT WHITE
			93m = BRIGHT YELLOW
			91 m = BRIGHT RED
			*/
			LevelColorChannel m_ColorChannels = { "\x1B[97m" ,"\x1B[93m" ,"\x1B[91m" };

			/*Default established color*/
			const char* m_Color = m_ColorChannels.WHITE;
		};
	}
}