#pragma once

#include <string.h>

#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/IndexBuffer.h"
#include "Components/Component.h"

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
			
			template<typename T>
			inline void AddComponent(Component::Component* c) 
			{
				if(m_Components.find(typeid(T).name()) == m_Components.end())
					m_Components[typeid(T).name()] = c; 
			}
			
			inline Renderer::Shader& GetShader() { return m_Shader; }
			inline std::string& GetName() { return m_Name; }
			
			template<typename T>
			T* GetComponent()
			{
				for (auto elem : m_Components)
				{
					if (elem.first == typeid(T).name())
						return (T*)elem.second;
				}

				return nullptr;
			}

		private:

			Renderer::VertexBuffer m_VBO;
			Renderer::IndexBuffer m_IBO;
			Renderer::Shader m_Shader;
			
			std::string m_Name;
			
			std::unordered_map<const char*, Component::Component*> m_Components;
		};
	}
}


