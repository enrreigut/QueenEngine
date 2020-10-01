#pragma once

namespace Queen
{
	namespace Utils
	{

		template<class T>
		class Singleton
		{
		public:

			Singleton(const Singleton&) = delete;
			Singleton& operator=(const Singleton) = delete;

			static T& Get()
			{
				static T s_Instance;
				return s_Instance;
			}

		protected:

			Singleton<T>() {};
			~Singleton<T>() {};
		};
	}
}