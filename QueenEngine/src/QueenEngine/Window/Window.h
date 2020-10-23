#pragma once

#include <iostream>
#include <functional>
#include <GLFW/glfw3.h>

#include <thread>

namespace Queen
{
	namespace Window
	{
		typedef unsigned int uint;

		class Window
		{
		public:

			Window();
			~Window();

			bool Init(const char* title, uint& width, uint& height);
			bool Shutdown();
			
			void SetContext();
			void Update();
			void Render();

			inline bool isRunning() { return m_Running && !glfwWindowShouldClose(m_Window); }
			
			//Getters
			inline GLFWwindow* GetWindowHandler() { return m_Window; }
			inline uint& GetWidth() { return m_Width; }
			inline uint& GetHeight() { return m_Height; }

			//Setters
			inline void SetWidth(uint& width) { m_Width = width; }
			void SetHeight(uint& height) { m_Height = height; }

		private:

			GLFWwindow* m_Window = nullptr;

			const char* m_Title = "Defaut";
			uint m_Width = 1080;
			uint m_Height = 720;

			bool m_Running = false;
		};
	}
}

