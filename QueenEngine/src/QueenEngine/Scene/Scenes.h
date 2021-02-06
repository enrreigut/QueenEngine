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
		struct SceneComponentElement
		{
			std::unordered_map<const char*, Entity::Entity*> m_SceneEntities;
			std::unordered_map<const char*, Entity::Entity*> m_SceneCameras;
			Entity::Entity* m_TargetCamera;
			Entity::Entity* m_MainCamera;
			const char* m_SceneName = "Default";
			float m_Width = 0.0f;
			float m_Height = 0.0f;

			float m_Left = 0.0f;
			float m_Right = 0.0f;
			float m_Top = 0.0f;
			float m_Bottom = 0.0f;
		};

		class Scene
		{
		public:

			Scene(const char* name);
			~Scene();

			inline SceneComponentElement* GetSceneConfiguration()& { return m_SceneConfiguration; }
			inline Renderer::VertexArray& GetVAO(){ return m_VAO; }

			void Load();

		private:

			SceneComponentElement* m_SceneConfiguration;
			Renderer::VertexArray m_VAO;
		};
	}
}


