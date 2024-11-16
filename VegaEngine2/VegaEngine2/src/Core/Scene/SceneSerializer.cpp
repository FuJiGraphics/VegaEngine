#include "pch.h"
#include "SceneSerializer.h"
#include "EntitySerializer.h"

namespace fz {
	SceneSerializer::SceneSerializer()
		: m_Scene(nullptr)
	{
		// Empty
	}

	SceneSerializer::SceneSerializer(const Shared<Scene>& scene)
		: m_Scene(scene)
	{
		// Empty
	}

	void SceneSerializer::SetTargetScene(const Shared<Scene>& scene)
	{
		m_Scene = scene;
	}

	void SceneSerializer::Serialize(const std::string& path)
	{
		if (!m_Scene)
			return;
		Database::LoadFromJson(path);
		auto& json = Database::GetJsonObject(path);
		json.clear();
		std::string sceneUUID = m_Scene->m_UUID;
		for (auto& it : m_Scene->m_EntityPool)
		{
			Entity entity = { it.first, it.second, m_Scene };
			EntitySerializer entitySerializer(sceneUUID, entity);
			entitySerializer.Serialize(path);
		}

		Database::Unload(path);
	}

	void SceneSerializer::SerializeRuntime(const std::string& path)
	{
		FZLOG_ASSERT(false, "");
	}

	Shared<Scene> SceneSerializer::Deserialize(const std::string& path)
	{
		Database::LoadFromJson(path);
		auto& json = Database::GetJsonObject(path);

		Shared<Scene> newScene = nullptr;
		for (json::iterator itSceneUUID = json.begin(); itSceneUUID != json.end(); ++itSceneUUID)
		{
			const std::string& sceneUUID = itSceneUUID.key();
			newScene = CreateShared<Scene>(1024, 768, 1, sceneUUID);
			for (json::iterator itEntityUUID = json[sceneUUID].begin(); itEntityUUID != json[sceneUUID].end(); ++itEntityUUID)
			{
				const std::string& entityUUID = itEntityUUID.key();
				std::string tagName = json[sceneUUID][entityUUID]["TagComponent"]["Tag"];
				fz::Entity entity = newScene->CreateEntity(entityUUID, tagName);
				EntitySerializer serialize(sceneUUID, entity);
				serialize.Deserialize(path);
			}
			break;
		}
		return newScene;
	}

	bool SceneSerializer::DeserializeRuntime(const std::string& path)
	{
		// ¹Ì±¸Çö
		FZLOG_ASSERT(false, "");
		return false;
	}

} // namespace fz