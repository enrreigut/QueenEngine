#pragma once

#include <unordered_map>
#include <string.h>

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

			void CreateScene(std::string name);
			void AddScene(Scenes::Scene* scene);
			void RemoveScene(std::string scene);
			void ClearAllScenes();
			void SetSceneAsDefault(std::string name);

			Scenes::Scene* GetDeafultScene();

		private:

			SceneManager();
			~SceneManager();

			std::unordered_map<std::string, Scenes::Scene*> m_Scenes;
		};
	}
}

