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


			void InitEngine();
			void Shutdown();

			void Start();
			void OnEvent();
			void Run();

			void LoadScene(Scenes::Scene& scene);
			void CalculateFPS();

		private:

			Window::Window* m_Window = nullptr;

			const char* m_Title = "DEFAULT";
			Window::uint m_Width = 1080;
			Window::uint m_Height = 720;

			Window::uint m_Frames = 0;
			double m_LastTime = 0.0;	

			//RENDERER STUFF
			Scenes::Scene* m_CurrentScene;
			//FRAME BUFFER
			Renderer::FrameBuffer m_FBO;
		};
	}
}

