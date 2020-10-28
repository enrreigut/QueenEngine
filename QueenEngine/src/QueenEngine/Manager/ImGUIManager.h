#pragma once

#include "../Vendor/ImGUI/imgui.h"
#include "../Vendor/ImGUI/imgui_impl_glfw.h"
#include "../Vendor/ImGUI/imgui_impl_opengl3.h"

#include "Manager.h"
#include "LogManager.h"
#include "../Window/Window.h"
#include "../GUI/ImGuiLogger.h"

namespace Queen
{
	namespace Managers
	{
		class ImGUIManager : public Manager, public Utils::Singleton<ImGUIManager>
		{
			friend class Utils::Singleton<ImGUIManager>;

		public:

			ImGUIManager();
			~ImGUIManager();

			void Start() override;
			void Shutdown() override;

			void AddContext();
			void Init(Window::Window* wind, const char* glsl_version);
			void OnRender();

		protected:

			bool showDockspace = true;
			bool showLog = true;
			bool showConsole = true;
			ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

			bool CreateDockspace(bool* p_open);
			bool CreateLog(bool* p_open);
			bool CreateConsole(bool* p_open);

			ImGuiIO m_io;

		private:

		};
	}
}


