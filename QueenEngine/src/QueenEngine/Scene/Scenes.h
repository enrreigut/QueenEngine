#pragma once

#include <unordered_map>
#include <string.h>

#include "../Entity/Entity.h"
#include "../Renderer/VertexArray.h"

namespace Queen
{
	namespace Scenes
	{
		class Scene
		{
		public:

			Scene(std::string name);
			~Scene();

			void Load();
			void RenderScene();
			void AddEntity(Entity::Entity* e);
			void DeleteEntity(Entity::Entity* e);

			inline std::string& GetSceneName() { return m_SceneName; }
			inline Renderer::VertexArray& GetVAO(){ return m_VAO; }

		private:

			std::string m_SceneName;
			Renderer::VertexArray m_VAO;
			std::unordered_map<std::string, Entity::Entity*> m_Entities;

		};
	}
}


