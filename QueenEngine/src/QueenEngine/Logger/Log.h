#pragma once

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <sstream>

#include "../Manager/Manager.h"
#include "../Utils/Timer.h"
#include "../Utils/StringUtils.h"

#include "../GUI/ImGuiLogger.h"

//This file is the Log header which is just an interface for the class which handles the Log console outputing with an established format.

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
			const char* GREEN;
		};

		class Log
		{
		public:

			Log() {}
			~Log() {}

			/*Levels of the Logger*/
			enum class Level { TRACE = 0, INFO = 1, WARN = 2, ERROR = 3, SUCCESS = 4 };

			/*Set name for the Logger in other to identify them if more than one is created. For Logger Management go to Manager/LogManager.cpp/h */
			void setName(const char* name) { m_Name = name; }

			/*This is used to set the color in which text will be outputed according to its Level*/
			const char* getLevelRepresentation(Level& l);

			/*Method for outputing to console. We pass the desired level and the message*/
			void LogMsg(Level l, const char* msg);

			void GUILogMsg(Level l, GUI::Logger& logger, const char* msg);

			/*Method for outputing to console with parameters if wanted.
			The parameters are custom added and for now just supports only string parameters.
			Way of usage:
			"Hello my name is {v}"and {v} is where the parameter would be displayed
			*/

			template<typename Arg>
			std::ostream& getParams(std::ostream& o, Arg&& arg) { return o << std::forward<Arg>(arg); }

			template<typename Arg, typename ...Args>
			std::ostream& getParams(std::ostream& o, Arg&& arg, Args&&... args)
			{
				o << std::forward<Arg>(arg) << "~";
				return getParams(o, std::forward<Args>(args)...);
			}

			template<typename Arg, typename... Args>
			void LogMsgParam(Level l, const char* msg, Arg&& w, Args&&... li)
			{
				std::ostringstream o;
				getParams(o, w, li...);

				std::stringstream ss;
				std::string param;
				std::string s = msg;
				size_t pos = 0;

				/*for to replace the {v} with the correct parameters*/
				for (auto elem : Split(o.str(), "~"))
				{
					pos = s.find("{v}");

					if (pos == std::string::npos)
						break;

					s.replace(pos, 3, elem);
				}

				printf("%s[%s] %s(%s): %s\033[0m\n", m_Color, m_T.getDateAndTime(), m_Name, getLevelRepresentation(l), s.c_str());
			}

			template<typename Arg, typename... Args>
			void GUILogMsgParam(Level l, GUI::Logger& logger, const char* msg, Arg&& w, Args&&... li)
			{
				std::ostringstream o;
				getParams(o, w, li...);

				std::stringstream ss;
				std::string param;
				std::string s = msg;
				size_t pos = 0;

				/*for to replace the {v} with the correct parameters*/
				for (auto elem : Split(o.str(), "~"))
				{
					pos = s.find("{v}");

					if (pos == std::string::npos)
						break;

					s.replace(pos, 3, elem);
				}

				logger.AddLog("[%s] %s(%s): %s\n", m_T.getDateAndTime(), m_Name, getLevelRepresentation(l), s.c_str());
			}
			
		private:

			/*To establish moment of Log*/
			Utils::Timer m_T;

			/*Default name if one is not established*/
			const char* m_Name = "DEFAULT";

			/*Colors of output in ANSI depending on the level. The colors are BRIGHT WHITE, YELLOW AND RED
			97m = BRIGHT WHITE
			93m = BRIGHT YELLOW
			91m = BRIGHT RED
			37m = BRIGHT GREEN
			*/
			LevelColorChannel m_ColorChannels = { "\x1B[97m" ,"\x1B[93m" ,"\x1B[91m", "\x1B[92m"};

			/*Default established color*/
			const char* m_Color = m_ColorChannels.WHITE;
		};

	}
}