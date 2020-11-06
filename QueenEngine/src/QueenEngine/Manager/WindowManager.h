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

			/*
			Class which manages the main Widnow of the Application. This is a Singleton thus only one can be created and handles all the Window operations.
			The picked strategy is to have a default Window which handles all window operations.
			*/

			WindowManager();
			~WindowManager();

			void Start() override;
			void Shutdown() override;

			inline Window::Window* GetWWindow(const char* title)& { return m_Windows[title]; }

			/*Init the required lis because this are the ones handling all the windows back end*/
			bool InitGLFW();
			bool InitGLEW();

			/*Create the Window with the desired title, width and height*/
			bool CreateWWindow(const char* title, Window::uint& width, Window::uint& height);
			/*Destroy the window by its title === window name*/
			bool DestroyWWindow(const char* title);
			/*Destroy all Windows in case we need more than one*/
			bool DestroyAllWWindows();

			/*Setters*/
			void SetWindowWidth(Window::Window& wnd, Window::uint& width);
			void SetWindowHeight(Window::Window& wnd, Window::uint& width);
			void SetWindowWidth(const char* wndName, Window::uint& width);
			void SetWindowHeight(const char* wndName, Window::uint& height);

			void NotifyEvents(GLFWwindow* w, bool debug);

		private:

			bool m_GlwfInitialised = false;
			bool m_GlewInitialised = false;
			
			std::unordered_map<const char*, Window::Window*> m_Windows;		
		};
	}
}


