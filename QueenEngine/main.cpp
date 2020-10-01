#include <iostream>

#include "src/QueenEngine/Manager/LogManager.h"

int main()
{
	LogManager::Get().Start();

	LogManager::Get().CreateLog("Test");
	LogManager::Get().GetLog("Test").LogMsg(Log::Level::INFO, "Hola Mundo!");

	LogManager::Get().Shutdown();
	
	return 0;
}