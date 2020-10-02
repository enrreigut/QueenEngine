#include <iostream>

#include "src/QueenEngine/Manager/LogManager.h"
#include "src/QueenEngine/Manager/MemoryManager.h"

int main()
{
	Queen::Managers::LogManager::Get().Start();
	Queen::Managers::LogManager::Get().Start();
	Queen::Managers::MemoryManager::Get().Start();
	

	Queen::Managers::MemoryManager::Get().Shutdown();
	Queen::Managers::LogManager::Get().Shutdown();
	
	return 0;
}