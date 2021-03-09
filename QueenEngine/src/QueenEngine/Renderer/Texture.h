#pragma once

namespace Queen
{
	namespace Renderer
	{
		class Texture
		{
		public:

			Texture(const char* path);
			~Texture();

			void Bind(unsigned int slot = 0) const;
			void Unbind() const;

			inline int GetTextureId() const { return m_TextureId; }
			inline int GetWidth() const { return m_Width; }
			inline int GetHeight() const { return m_Height; }

		private:

			unsigned int m_TextureId;
			const char* m_FilePath;
			unsigned char* m_BufferData;
			int m_Width, m_Height, m_BPP;

		};
	}
}


