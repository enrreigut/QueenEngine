#include "RendererManager.h"

namespace Queen
{
	namespace Managers
	{

		RendererManager::RendererManager()
		{

		}

		RendererManager::~RendererManager()
		{
			QE_LOG(QE_TRACE, g_REN_MAN_INFO_DESTROYED);
		}

		void RendererManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;

				QE_LOG(QE_TRACE, g_REN_MAN_INFO_START);
			}
			else
			{
				QE_LOG(QE_ERROR, g_REN_MAN_ERROR_ALREADY_STARTED);
			}
		}

		void RendererManager::Shutdown()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_REN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				QE_LOG(QE_WARN, g_REN_MAN_INFO_SHUTDOWN);

				m_Running = false;
			}
		}

		void RendererManager::SetRenderScene()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_REN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				Queen::Managers::SceneManager::Get().GetDeafultScene()->Load();
			}
		}

		void RendererManager::CreateFrameBuffer()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_REN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				m_FBO.CreateFrameBuffer(1080, 720);
				m_FBO.CreateTexture();
				m_FBO.CreateRenderBuffer();
				m_FBO.Check();
			}
		}

		void RendererManager::RenderScene(Window::Window* window)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_REN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				Queen::Managers::SceneManager::Get().GetDeafultScene()->RenderScene(window);
			}
		}

		void RendererManager::RenderImGUI()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_REN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				Queen::Managers::ImGUIManager::Get().SetFramebuffer(m_FBO.GetFBO());
				Queen::Managers::ImGUIManager::Get().OnRender();
			}
		}

		void RendererManager::SetUniformFloat(Renderer::Shader& shader, const char* name, float& value)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_REN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				glUniform1f(glGetUniformLocation(shader.GetProgramID(), name), value);
			}
		}
	}
}