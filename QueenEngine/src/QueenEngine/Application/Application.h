#pragma once

#include "../QueenEngine.h"

namespace Queen
{
	namespace Application
	{
		class Application
		{
		public:

			Application();
			Application(const char* title, Window::uint&& width, Window::uint&& height);
			~Application();

			void Start();
			void Shutdown();
			void OnEvent();
			void Run();

		private:

			Window::Window* m_Window = nullptr;

			const char* m_Title = "DEFAULT";
			Window::uint m_Width = 1080;
			Window::uint m_Height = 720;

		};
	}
}

