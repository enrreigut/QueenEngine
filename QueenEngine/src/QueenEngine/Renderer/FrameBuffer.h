#pragma once

#include <GL/glew.h>
#include "glm/glm.hpp"

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
			void Resize(glm::vec2& newSize);

			void Bind();
			void Unbind();

			bool Check();
			void Delete();

			inline unsigned int GetFBO()& { return m_FBO; }
			inline unsigned int GetWidth()& { return m_Width; }
			inline unsigned int GetHeight()& { return m_Height; }

		private:

			unsigned int m_FBO = 0;
			unsigned int m_Texture = 0;
			unsigned int m_RBO = 0;

			unsigned int m_Width;
			unsigned int m_Height;

		};
	}
}