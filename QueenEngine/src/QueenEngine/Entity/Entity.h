#pragma once

#include <string.h>

#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/IndexBuffer.h"

#include "../Renderer/Shader.h"

namespace Queen
{
	namespace Entity
	{
		class Entity
		{
		public:

			Entity(std::string name);
			~Entity();

			/*Temporal Stuff*/

				GLfloat m_Data[8] =
				{
					-0.5f, -0.5f,
					0.5f, -0.5f,
					0.5f, 0.5f,
					-0.5f, 0.5f
				};

				unsigned int indices[6] =
				{
					0, 2, 3,
					0, 1, 2
				};

			/*========================*/

			void LoadEntity(Renderer::VertexArray& va, float* verts, size_t sizeV, unsigned int* indices, size_t sizeI);
			void LoadShader(const char* vertFilePath, const char* fragFilePath);
			void Draw(Renderer::VertexArray& val);

			inline Renderer::Shader& GetShader() { return m_Shader; }
			inline std::string& GetName() { return m_Name; }

		private:

			Renderer::VertexBuffer m_VBO;
			Renderer::IndexBuffer m_IBO;
			Renderer::Shader m_Shader;

			std::string m_Name;

		};
	}
}


