#pragma once

#include <unordered_map>
#include "Manager.h"
#include "LogManager.h"

#include "../Window/Window.h"

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

			bool InitLibraries();
			bool CreateWWindow(const char* title, Window::uint& width, Window::uint& height);
			bool DestroyWWindow(const char* title);
			bool DestroyAllWWindows();

			//TODO
			void NotifyEvents(GLFWwindow* w, bool debug);

		private:

			bool m_GlwfInitialised = false;

			std::unordered_map<const char*, Window::Window*> m_Windows;			
		};
	}
}


