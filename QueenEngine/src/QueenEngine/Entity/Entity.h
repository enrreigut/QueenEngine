#pragma once

#include <string.h>

#include "Components/Component.h"

#include "../Manager/InputManager.h"

#include "../Renderer/Shader.h"

namespace Queen
{
	namespace Entity
	{
		class Entity
		{
		public:

			Entity(const char* name);
			~Entity();

			void LoadEntity();
			void Draw();
			void LoadShader(const char* vertFilePath, const char* fragFilePath);
			
			inline Renderer::Shader& GetShader() { return m_Shader; }
			inline const char* GetName()& { return m_Name; }

			template<typename T>
			inline void AddComponent(Component::Component* c) 
			{
				if(m_Components.find(typeid(T).name()) == m_Components.end())
					m_Components[typeid(T).name()] = c; 
			}
			
			template<typename T>
			void RemoveComponent()
			{
				for (auto elem : m_Components)
				{
					if (elem.first == typeid(T).name())
					{
						delete elem.second;
						m_Components.erase(elem.first);
					}
				}
			}

			void RemoveAllComponent()
			{
				for (auto it = m_Components.end(); it != m_Components.begin(); it--)
				{
					delete it->second;
					m_Components.erase(it);
				}
			}
			
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

			inline std::unordered_map<const char*, Component::Component*> GetAllComponents()& { return m_Components; }

			void SetTransform(glm::vec3 data);

		private:

			Renderer::VertexArray m_VAO;
			Renderer::VertexBuffer m_VBO;
			Renderer::IndexBuffer m_IBO;
			Renderer::Shader m_Shader;
			
			const char* m_Name;
			
			std::unordered_map<const char*, Component::Component*> m_Components;
		};
	}
}


