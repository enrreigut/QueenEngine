#pragma once

#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_glfw.h"
#include "../ImGUI/imgui_impl_opengl3.h"

#pragma comment(lib, "legacy_stdio_definitions")

#include "Manager.h"
#include "LogManager.h"
#include "../Window/Window.h"

namespace Queen
{
	namespace Managers
	{
		class ImGUIManager: public Manager, public Utils::Singleton<ImGUIManager>
		{
			friend class Utils::Singleton<ImGUIManager>;
		public:

			ImGUIManager();
			~ImGUIManager();

			void Start() override;
			void Shutdown() override;
			
			void CreateContext();
			void Init(Window::Window* wind, const char* glsl_version);
			void OnRender();

		protected:

			bool show_demo_window = true;
			bool show_another_window = false;
			ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		private:



		};
	}
}


