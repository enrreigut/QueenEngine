#pragma once

#include <cmath>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"

#include "Manager.h"
#include "LogManager.h"
#include "../GUI/ImGuiLogger.h"
#include "../Window/Window.h"

#include "RendererManager.h"
#include "SceneManager.h"

#include "../Renderer/FrameBuffer.h"

#include "../Vendor/ImGUI/imgui.h"
#include "../Vendor/ImGUI/imgui_impl_glfw.h"
#include "../Vendor/ImGUI/imgui_impl_opengl3.h"

#include "../Vendor/ImGuizmo/ImGuizmo.h"

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
			
			void CreateDockingWindows();

			void OnRender();

			inline Renderer::FrameBuffer* GetFrameBuffer() { return m_FBO; }
			inline glm::vec2 GetViewportSize()& { return m_ViewportSize; }

			void SetFramebuffer(Renderer::FrameBuffer* fbo) { m_FBO = fbo; }

		protected:

			bool showDockspace = true;
			bool showLog = true;
			bool showConsole = true;
			bool showViewport = true;
			bool showEntitySpec = true;
			bool showSceneEntity = true;
			ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

			//Selectables
			const char* m_Selected = "";

			bool CreateDockspace(bool* p_open);
			bool CreateLog(bool* p_open);
			bool CreateConsole(bool* p_open);
			bool CreateWindowWithImage(bool* p_open);
			bool CreateEntitiySpecifications(bool* p_open);
			bool CreateSceneEntities(bool* p_open);

			ImGuiIO m_io;

		private:

			Renderer::FrameBuffer* m_FBO;
			glm::vec2 m_ViewportSize = { 500.0f, 400.0f };

			bool m_IsFirstRender = true;
		};
	}
}


