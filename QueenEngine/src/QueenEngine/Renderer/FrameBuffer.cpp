#include "FrameBuffer.h"

namespace Queen
{
	namespace Renderer
	{
		
		FrameBuffer::FrameBuffer()
		{

		}

		FrameBuffer::~FrameBuffer()
		{
			Delete();
		}

		void FrameBuffer::CreateFrameBuffer(unsigned int width, unsigned int height)
		{
			m_Width = width;
			m_Height = height;

			if (m_FBO)
			{
				Delete();
			}

			glCreateFramebuffers(1, &m_FBO);
			Bind();
		}

		void FrameBuffer::CreateTexture()
		{
			glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);
			glBindTexture(GL_TEXTURE_2D, m_Texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);
		}

		void FrameBuffer::CreateRenderBuffer()
		{
			glCreateTextures(GL_TEXTURE_2D, 1, &m_RBO);
			glBindTexture(GL_TEXTURE_2D, m_RBO);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Width, m_Height);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_RBO, 0);
		}

		void FrameBuffer::Resize(glm::vec2& newSize)
		{
			m_Width = newSize.x;
			m_Height = newSize.y;

			CreateFrameBuffer(m_Width, m_Height);
			CreateTexture();
			CreateRenderBuffer();
			Check();
		}

		void FrameBuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
			glViewport(0, 0, m_Width, m_Height);
		}

		void FrameBuffer::Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);			
		}

		bool FrameBuffer::Check()
		{
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				//Error
				return false;
			}
			else
			{
				Unbind();
				return true;
			}
		}

		void FrameBuffer::Delete()
		{
			glDeleteFramebuffers(1, &m_FBO);
			glDeleteTextures(1, &m_Texture);
			glDeleteTextures(1, &m_RBO);
		}

	}
}

