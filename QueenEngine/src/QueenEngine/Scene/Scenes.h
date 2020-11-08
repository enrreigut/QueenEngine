#pragma once

#include <unordered_map>
#include <string.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
			void RenderScene(float sizeX, float sizeY);
			void AddEntity(Entity::Entity* e);
			void DeleteEntity(Entity::Entity* e);

			inline std::string& GetSceneName() { return m_SceneName; }
			inline Renderer::VertexArray& GetVAO(){ return m_VAO; }

			inline bool IsDefault()& { return m_Default; }
			inline void SetDefault(bool b) { m_Default = b; }
			inline void SetCameraProj(Entity::Entity& camera) { m_Camera = &camera; }

		private:

			bool m_Default = false;
			std::string m_SceneName;
			Renderer::VertexArray m_VAO;
			
			std::unordered_map<std::string, Entity::Entity*> m_Entities;
			Entity::Entity* m_Camera;
		};
	}
}


