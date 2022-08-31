#pragma once

namespace Queen
{
	namespace Utils
	{
		/*
		
		Generic Singleton class. Considered a bad practice due to thread issues and redundancy. However for the thought design it will not affect much.
		Maybe just could try to only instantiate once the class and be careful but since the Singleton pattern can be made thread safe and this GameEngine
		will run just in one thread, and for the sake of the project there is no problem.
		
		*/
		template<class T>
		class Singleton
		{
		public:

			/*Remove copy operators*/
			Singleton(const Singleton&) = delete;
			Singleton& operator=(const Singleton) = delete;
			
			/*Just return the instance of the class*/
			static T& Get()
			{
				static T s_Instance;
				return s_Instance;
			}

		protected:

			/*COnstructor and Destructor in protected so they cannot be created more than once*/
			Singleton<T>() {};
			~Singleton<T>() {};
		};
	}
}