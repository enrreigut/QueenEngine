#pragma once

#include <unordered_map>

#include "Manager.h"
#include "LogManager.h"
#include "../Window/Window.h"
#include "InputManager.h"

namespace Queen
{
	namespace Managers
	{
		class WindowManager : public Manager, public Utils::Singleton<WindowManager>
		{
			friend class Utils::Singleton<WindowManager>;
		public:

			WindowManager();
			~WindowManager();

			void Start() override;
			void Shutdown() override;

			inline Window::Window* GetWWindow(const char* title)& { return m_Windows[title]; }

			bool InitGLFW();
			bool InitGLEW();
			bool CreateWWindow(const char* title, Window::uint& width, Window::uint& height);
			bool DestroyWWindow(const char* title);
			bool DestroyAllWWindows();


			void SetWindowWidth(Window::Window& wnd, Window::uint& width);
			void SetWindowHeight(Window::Window& wnd, Window::uint& width);
			void SetWindowWidth(const char* wndName, Window::uint& width);
			void SetWindowHeight(const char* wndName, Window::uint& height);

			//TODO
			void NotifyEvents(GLFWwindow* w, bool debug);

		private:

			bool m_GlwfInitialised = false;
			bool m_GlewInitialised = false;
			
			std::unordered_map<const char*, Window::Window*> m_Windows;		
		};
	}
}


