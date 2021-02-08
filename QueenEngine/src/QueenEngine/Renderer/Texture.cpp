#include "Texture.h"

#include "gl/glew.h"
#include "stbImage/stb_image.h"
#include "../Manager/LogManager.h"

namespace Queen
{
	namespace Renderer
	{
		Texture::Texture(const char* path)
			:m_TextureId(0), m_FilePath(path), m_BufferData(nullptr), m_Width(0), m_Height(0), m_BPP(0)		{

			stbi_set_flip_vertically_on_load(1);
			m_BufferData = stbi_load(path, &m_Width, &m_Height, &m_BPP, 4);

			if (m_BufferData == NULL)
				QE_LOG_PARAMS(QE_ERROR, "Error loading the texture at: {v}", path);

			glGenTextures(1, &m_TextureId);
			glBindTexture(GL_TEXTURE_2D, m_TextureId);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_BufferData);
			glBindTexture(GL_TEXTURE_2D, 0);

			if (m_BufferData)
				stbi_image_free(m_BufferData);
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_TextureId);
		}

		void Texture::Bind(unsigned int slot) const
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, m_TextureId);
		}

		void Texture::Unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}