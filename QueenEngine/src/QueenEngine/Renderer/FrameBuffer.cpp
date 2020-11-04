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

		}

		void FrameBuffer::CreateFrameBuffer()
		{
			glCreateFramebuffers(1, &m_FBO);
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		}

		void FrameBuffer::CreateTexture()
		{
			glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);
			glBindTexture(GL_TEXTURE_2D, m_Texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1080, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);
		}

		void FrameBuffer::CreateRenderBuffer()
		{
			glCreateTextures(GL_TEXTURE_2D, 1, &m_RBO);
			glBindTexture(GL_TEXTURE_2D, m_RBO);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, 1080, 720);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_RBO, 0);
		}

		void FrameBuffer::Bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
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
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				return true;
			}
		}

		void FrameBuffer::Delete()
		{
			glDeleteFramebuffers(1, &m_FBO);
		}

	}
}

