#pragma once

#include <unordered_map>

#include "../Utils/Singleton.h"

#include "Manager.h"
#include "LogManager.h"

#include "../Scene/Scenes.h"

namespace Queen
{
	namespace Managers
	{
		class SceneManager : public Manager, public Utils::Singleton<SceneManager>
		{
			friend class Singleton<SceneManager>;

		public:

			void Start() override;
			void Shutdown() override;

			void CreateScene(const char* sceneName, const char* path);

			void AddSceneToQueue(Scenes::Scene* scene);
			void RemoveSceneFromQueue(const char* sceneName);
			void ClearSceneQueue();

			bool CheckSceneExistence(const char* sceneName);

			//Getters
			Scenes::Scene* GetRenderScene();
			Scenes::Scene* GetScene(const char* sceneName);
			inline float GetRenderSceneWidth()& { return m_RenderScene->GetSceneConfiguration()->m_Width; }
			inline float GetRenderSceneHeight()& { return m_RenderScene->GetSceneConfiguration()->m_Height; }
			inline float GetSceneWidth(const char* sceneName)& { return m_SceneQueue.find(sceneName) == m_SceneQueue.end() ? 0.0f : m_SceneQueue.find(sceneName)->second->GetSceneConfiguration()->m_Width; }
			inline float GetSceneHeight(const char* sceneName)& { return m_SceneQueue.find(sceneName) == m_SceneQueue.end() ? 0.0f : m_SceneQueue.find(sceneName)->second->GetSceneConfiguration()->m_Height; }

			//Setters
			void SetSceneAsRender(const char* sceneName);

			void SetRenderSceneWidth(float width);
			void SetRenderSceneHeight(float height);
			void SetRenderSceneLeft(float xpos);
			void SetRenderSceneRight(float ypos);
			void SetRenderSceneTop(float ypos);
			void SetRenderSceneBottom(float ypos);

			void SetSceneWidth(const char* sceneName, float width);
			void SetSceneHeight(const char* sceneName, float height);

			//Sets Render Camera of Render Scene
			void SetRenderCamera(const char* cameraName);
			void SetMainCamera(const char* cameraName);

			//Derived
			void SaveRenderScene();

		private:

			SceneManager();
			~SceneManager();

			Scenes::Scene* m_RenderScene = nullptr;
			std::unordered_map<const char*, Scenes::Scene*> m_SceneQueue;
		};
	}
}

