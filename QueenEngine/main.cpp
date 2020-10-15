#include <iostream>

#include "src/QueenEngine/Manager/LogManager.h"
#include "src/QueenEngine/Manager/MemoryManager.h"
#include "src/QueenEngine/Manager/EventManager.h"

//For test purposes only
#include "src/QueenEngine/MemoryPool/Pool.h"
#include "src/QueenEngine/Event/ApplicationEvent.h"

int main()
{
	Queen::Managers::LogManager::Get().Start();
	Queen::Managers::MemoryManager::Get().Start();
	Queen::Managers::EventManager::Get().Start();
	
	//TESING POOL MANAGER = Test of how Pool Manager Works
	/*

	struct Test
	{
		static Queen::Memory::Pool s_allocator;

		uint64_t data[2];

		static void* operator new(size_t size)
		{
			return s_allocator.Allocate(size);
		}

		static void operator delete(void *ptr, size_t size)
		{
			return s_allocator.Deallocate(ptr, size);
		}
	};

	Queen::Memory::Pool Test::s_allocator{ 8 };

	Test* test[10];

	std::cout << "Size of Test Object: " << sizeof(Test) << " bytes" << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		test[i] = new Test();
		std::cout << "new[" << i << "] = " << test[i] << " test" << std::endl;
	}

	std::cout << std::endl;

	for (int i = 9; i >= 4; --i)
	{
		std::cout << "delete[" << i << "] = " << test[i] << " test" << std::endl;
		delete test[i];
	}

	for (int i = 0; i < 3; ++i)
	{
		test[i] = new Test();
		std::cout << "new[" << i << "] = " << test[i] << " test" << std::endl;
	}
	*/
	//END TESTING POOL MANAGER

	//TESTIN EVENTS
	/*
	Queen::System::Log l;
	l.setName("EVENTS");

	Queen::Event::WindowResizeEvent e(1080, 720);

	if(e.IsInCategory(Queen::Event::EventCategory::EC_APPLICATION))
		l.LogMsgParam(Queen::System::Log::Level::SUCCESS, "{v}.", e);
	*/
	//END TESTING EVENTS

	Queen::Managers::EventManager::Get().Shutdown();
	Queen::Managers::MemoryManager::Get().Shutdown();	
	Queen::Managers::LogManager::Get().Shutdown();

	return 0;
}