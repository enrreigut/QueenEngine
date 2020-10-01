#include <iostream>

#include "src/QueenEngine/Manager/LogManager.h"

int main()
{
	Queen::Managers::LogManager::Get().Start();

	Queen::Managers::LogManager::Get().CreateLog("Test");
	Queen::Managers::LogManager::Get().GetLog("Test").LogMsg(Queen::System::Log::Level::WARN, "Hola Mundo!");

	Queen::Managers::LogManager::Get().Shutdown();
	
	return 0;
}