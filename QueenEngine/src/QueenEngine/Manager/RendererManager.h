#pragma once

#include "../Utils/Singleton.h"

#include "Manager.h"
#include "LogManager.h"
#include "SceneManager.h"
#include "ImGUIManager.h"
#include "WindowManager.h"
#include "EntityManager.h"

#include "../Renderer/Shader.h"

#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/IndexBuffer.h"
#include "../Renderer/FrameBuffer.h"

#include "glm/glm.hpp"

namespace Queen
{
	namespace Managers
	{
		class RendererManager : public Manager, public Utils::Singleton<RendererManager>
		{
			friend class Utils::Singleton<RendererManager>;
		public:

			void Start() override;
			void Shutdown() override;

			void CreateFrameBuffer(float sizeX, float sizeY);
			inline void BindFrameBuffer() { m_FBO.Bind(); }
			inline void UnbindFrameBuffer() { m_FBO.Unbind(); }

			void RenderScene(bool debugRender);
			void RenderImGUI();			

			void SetRenderScene();
			void SetUniformFloat(Renderer::Shader& shader, const char* name, float& value);

		private:

			RendererManager();
			~RendererManager();

			Renderer::FrameBuffer m_FBO;

		};
	}
}