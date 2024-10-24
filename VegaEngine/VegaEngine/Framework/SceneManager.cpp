#include "Core/stdafx.h"
#include "SceneManager.h"
#include "Core/Scene/SceneList.h"

namespace fz {

	SceneList SceneManager::s_SceneList;

	void SceneManager::Release()
	{
		if (s_SceneList.empty())
			return;

		s_SceneList.Release();
	}

	Scene* SceneManager::GetCurrentScene()
	{
		if (s_SceneList.empty())
			return nullptr;

		auto scene = s_SceneList.GetCurrentScene();
		return (*scene);
	}

	void SceneManager::InsertScene(const std::string& sceneID)
	{
		s_SceneList.InsertScene(sceneID);
	}

	void SceneManager::RemoveScene(const std::string& sceneID)
	{
		if (s_SceneList.empty())
			return;

		s_SceneList.RemoveScene(sceneID);
	}

	void SceneManager::ChangeScene(const std::string& sceneID)
	{
		if (s_SceneList.empty())
			return;

		s_SceneList.ChangeScene(sceneID);
	}

	void SceneManager::Event(EventList& events)
	{
		if (s_SceneList.empty())
			return;

		s_SceneList.Event(events);
	}

	void SceneManager::Update(float dt)
	{
		if (s_SceneList.empty())
			return;

		s_SceneList.Update(dt);
	}

	void SceneManager::Draw(fz::Window& window)
	{
		if (s_SceneList.empty())
			return;

		s_SceneList.Draw(window);
	}

	void SceneManager::DrawGui()
	{
		if (s_SceneList.empty())
			return;

		s_SceneList.DrawGui();
	}

	void SceneManager::Collision()
	{
		if (s_SceneList.empty())
			return;

		s_SceneList.Collision();
	}

	void SceneManager::DisplayCollider(fz::Window& window)
	{
		if (s_SceneList.empty())
			return;

		s_SceneList.DrawCollisionSystem(window);
	}

	void SceneManager::UpdateCollider()
	{
		if (s_SceneList.empty())
			return;

		s_SceneList.UpdateCollider();
	}

} // namespace fz