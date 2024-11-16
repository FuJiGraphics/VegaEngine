#include "pch.h"
#include "SceneSerializer.h"

namespace fz {

	SceneSerializer::SceneSerializer(const Shared<Scene>& scene)
		: m_Scene(scene)
	{
		// Empty
	}

	void SceneSerializer::Serialize(const std::string& path)
	{

	}

	void SceneSerializer::SerializeRuntime(const std::string& path)
	{
		FZLOG_ASSERT(false, "");
	}

	bool SceneSerializer::Deserialize(const std::string& path)
	{
		return false;
	}

	bool SceneSerializer::DeserializeRuntime(const std::string& path)
	{
		// ¹Ì±¸Çö
		FZLOG_ASSERT(false, "");
		return false;
	}

} // namespace fz