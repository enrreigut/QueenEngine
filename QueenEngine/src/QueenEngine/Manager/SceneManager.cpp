#include "SceneManager.h"

namespace Queen
{
	namespace Managers
	{
		SceneManager::SceneManager()
		{

		}

		SceneManager::~SceneManager()
		{
			QE_LOG(QE_TRACE, g_SCN_MAN_INFO_DESTROYED);
		}

		void SceneManager::Start()
		{
			if (!m_Running)
			{
				m_Running = true;

				QE_LOG(QE_TRACE, g_SCN_MAN_INFO_START);
			}
			else
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_ALREADY_STARTED);
			}
		}

		void SceneManager::Shutdown()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				QE_LOG(QE_WARN, g_SCN_MAN_INFO_SHUTDOWN);

				m_Running = false;
			}
		}

		void SceneManager::CreateScene(std::string name)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_Scenes.find(name) != m_Scenes.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "A scene with {v} as name, already exists.", name);
				}
				else
				{
					Scenes::Scene* scene = new Scenes::Scene(name);
					m_Scenes[name] = scene;
				}
			}
		}

		void SceneManager::AddScene(Scenes::Scene* scene)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_Scenes.find(scene->GetSceneName()) != m_Scenes.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "A scene with {v} as name, already exists.", scene->GetSceneName());
				}
				else
				{
					m_Scenes[scene->GetSceneName()] = scene;
				}
			}
		}

		void SceneManager::RemoveScene(std::string name)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_Scenes.find(name) == m_Scenes.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "A scene with {v} as name, do not exist.", name);
				}
				else
				{
					delete m_Scenes.find(name)->second;
					m_Scenes.erase(name);
				}
			}
		}

		void SceneManager::ClearAllScenes()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				for (auto& scene : m_Scenes)
				{
					delete scene.second;
				}

				m_Scenes.clear();
			}
		}

		void SceneManager::SetSceneAsDefault(std::string name)
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				if (m_Scenes.find(name) == m_Scenes.end())
				{
					QE_LOG_PARAMS(QE_ERROR, "A scene with {v} as name, do not exist.", name);
				}
				else
				{

					for (auto& scene : m_Scenes)
					{
						if (scene.second->IsDefault() && scene.first != name)
							scene.second->SetDefault(false);
					}

					m_Scenes[name]->SetDefault(true);
				}
			}
		}

		Scenes::Scene* SceneManager::GetDeafultScene()
		{
			if (!m_Running)
			{
				QE_LOG(QE_ERROR, g_SCN_MAN_ERROR_NOT_STARTED);
			}
			else
			{
				for (auto& scene : m_Scenes)
				{
					if (scene.second->IsDefault())
						return scene.second;
				}

			}
			
			return nullptr;
		}
	}
}