#pragma once

#include <unordered_map>
#include <vector>

#include "../Utils/Singleton.h"

#include "Manager.h"
#include "LogManager.h"
#include "WindowManager.h"

#include "SceneManager.h"
#include "../Entity/Entity.h"

#include "ImGuizmo/ImGuizmo.h"

namespace Queen
{
	namespace Managers
	{

		class EntityManager : public Manager, public Utils::Singleton<EntityManager>
		{

			friend class Utils::Singleton<EntityManager>;

		public:

			void Start() override;
			void Shutdown() override;

			Entity::Entity* CreateCamera(Scenes::Scene* scene, const char* entityName);
			Entity::Entity* CreateEntity(Scenes::Scene* scene, const char* entityName);

			Entity::Entity* CreateCamera(const char* sceneName, const char* entityName);
			Entity::Entity* CreateEntity(const char* sceneName, const char* entityName);

			Entity::Entity* CreateCameraInRenderScene(const char* entityName);
			Entity::Entity* CreateEntityInRenderScene(const char* entityName);

			void AddEntity(Scenes::Scene* scene, Entity::Entity* entity);
			void AddEntity(const char* sceneName, Entity::Entity* entity);
			void AddEntityToRenderScene(Entity::Entity* entity);

			void CalculateCamera(bool debugRender);
			void DrawEntity(Entity::Entity* entity);

		private:

			EntityManager();
			~EntityManager();
		};
	}
}