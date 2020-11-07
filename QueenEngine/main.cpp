#include <iostream>
#include "src/QueenEngine/Application/Application.h"

//For test purposes only
//#include "src/QueenEngine/MemoryPool/Pool.h"
//#include "src/QueenEngine/Event/ApplicationEvent.h"

#include "src/QueenEngine/Entity/Components/Component.h"

int main()
{	
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

	//app.CreateQuad("quad01");
	//intantiate a Quad with a transform component

	Queen::Scenes::Scene test_scene("Test Scene");
	test_scene.SetDefault(true);

	/* Add Camera */



	/* Default Model */

	Queen::Entity::Entity main_cube("Cube");
	Queen::Entity::Component::Model m;
	m.LoadObj("Resources/Model/Test/bunny.obj");
	main_cube.AddComponent<Queen::Entity::Component::Model>(&m);

	test_scene.AddEntity(&main_cube);

	/* Add Scenes */

	Queen::Scenes::Scene test_scene_two("Test Scene 2");
	Queen::Scenes::Scene test_scene_three("Test Scene 3");

	Queen::Application::Application app("QueenEngine", 1080, 720);
	app.InitEngine();

	app.LoadScene(test_scene);
	app.LoadScene(test_scene_two);
	app.LoadScene(test_scene_three);

	app.Start();
	app.Run();
	app.Shutdown();
	
	return 0;
}