#include "Core/stdafx.h"
#include "SceneList.h"

namespace fz {

	SceneList::SceneList()
		: m_CurrScene(0)
	{
		// Empty
	}

	SceneList::~SceneList()
	{
		this->Release();
	}

	void SceneList::Release()
	{
		for (Scene* scene : *this)
		{
			if (scene != nullptr)
			{
				scene->Release();
				delete scene;
				scene = nullptr;
			}
		}
	}

	void SceneList::InsertScene(const std::string& sceneID)
	{
		Scene* newScene = new Scene;
		newScene->Init(sceneID);
		Super::insert(newScene);
	}

	void SceneList::RemoveScene(const std::string& sceneID)
	{
		Scene** target = nullptr;
		for (Scene*& scene : *this)
		{
			if (scene->GetSceneID() == sceneID)
			{
				target = &scene;
				break;
			}
		}
		if (target != nullptr)
		{
			(*target)->Release();
			Super::remove(*target);
			delete (*target);
			(*target) = nullptr;
		}
	}

	void SceneList::ChangeScene(const std::string& sceneID)
	{
		int index = 0;
		for (auto iter : *this)
		{
			if (iter->GetSceneID() == sceneID)
				break;
			index++;
		}
		m_CurrScene = index;
	}

	void SceneList::Event(EventList& events)
	{
		Iter scene = (Super::begin() + m_CurrScene);
		(*scene)->Event(events);
	}

	void SceneList::Update(float dt)
	{
		Iter scene = (Super::begin() + m_CurrScene);
		(*scene)->Update(dt);
	}

	void SceneList::Draw(Window& window)
	{
		Iter scene = (Super::begin() + m_CurrScene);
		(*scene)->Draw(window);
	}

	void SceneList::DrawGui()
	{
		Iter scene = (Super::begin() + m_CurrScene);
		(*scene)->DrawGui();
	}

	void SceneList::Collision()
	{
		
	}

} // namespace fz