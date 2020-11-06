#pragma once

#include <string.h>

#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/IndexBuffer.h"
#include "Model.h"

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

			void LoadEntity(Renderer::VertexArray& va);
			void LoadShader(const char* vertFilePath, const char* fragFilePath);
			void Draw(Renderer::VertexArray& val);
			void AddModel(const char* filePath);

			inline Renderer::Shader& GetShader() { return m_Shader; }
			inline Component::Model GetModel() { return m_Model; }
			inline std::string& GetName() { return m_Name; }

		private:

			Renderer::VertexBuffer m_VBO;
			Renderer::IndexBuffer m_IBO;
			Renderer::Shader m_Shader;
			Component::Model m_Model;

			std::string m_Name;

		};
	}
}


