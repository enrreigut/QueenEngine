#pragma once

#include <GL/glew.h>

namespace Queen
{
	namespace Renderer
	{
		class FrameBuffer
		{
		public:

			FrameBuffer();
			~FrameBuffer();

			void CreateFrameBuffer(unsigned int width, unsigned int height);
			void CreateTexture();
			void CreateRenderBuffer();

			void Bind();
			void Unbind();

			bool Check();
			void Delete();

			inline unsigned int GetFBO()& { return m_FBO; }

		private:

			unsigned int m_FBO;
			unsigned int m_Texture;
			unsigned int m_RBO;

			unsigned int m_Width;
			unsigned int m_Height;

		};
	}
}

