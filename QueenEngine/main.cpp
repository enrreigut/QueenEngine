#include <iostream>
#include "src/QueenEngine/Application/Application.h"

//For test purposes only
//#include "src/QueenEngine/MemoryPool/Pool.h"
//#include "src/QueenEngine/Event/ApplicationEvent.h"

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
	
	//END TESTING POOL MANAGER

	//TESTIN EVENTS

	Queen::System::Log l;
	l.setName("EVENTS");

	Queen::Event::WindowResizeEvent e(1080, 720);

	if(e.IsInCategory(Queen::Event::EventCategory::EC_APPLICATION))
		l.LogMsgParam(Queen::System::Log::Level::SUCCESS, "{v}.", e);
	*/
	//END TESTING EVENTS

	Queen::Application::Application app("QueenEngine", 1080, 720);
	app.SetDebugRender(true);
	app.InitEngine();

	Queen::Entity::Entity* e = Queen::Managers::EntityManager::Get().CreateEntityInRenderScene("Mario");
	Queen::Entity::Component::Model m;
	m.LoadObj("Resources/Model/Test/Mario.obj");
	e->AddComponent<Queen::Entity::Component::Model>(&m);
	e->SetTransform(glm::vec3(0.0f, 0.0f, 0.0f));
	Queen::Entity::Component::Material mat;
	e->AddComponent<Queen::Entity::Component::Material>(&mat);

	Queen::Entity::Entity* e2 = Queen::Managers::EntityManager::Get().CreateEntityInRenderScene("Casco");
	Queen::Entity::Component::Model m2;
	m2.LoadObj("Resources/Model/Test/duck.obj");
	e2->AddComponent<Queen::Entity::Component::Model>(&m2);
	e2->SetTransform(glm::vec3(3.0f, 0.0f, 0.0f));
	e2->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	Queen::Entity::Component::Material mat2;
	e2->AddComponent<Queen::Entity::Component::Material>(&mat2);

	// This should be on top of creating the entities, however, is in charge on loading entities. Need to FIX this.
	app.Start();

	// Add textures after FrameBuffer Creation so they do not render on top of the location assigned to them	
	// Entity 1
	mat.LoadTexture("Resources/Textures/Mario/mario_mime.png");
	
	//Entity2
	mat2.LoadTexture("Resources/Textures/Duck/duck.png");


	bool isPlayingGame = true;

	app.Run(isPlayingGame);
	app.Shutdown();
	
	return 0;
}