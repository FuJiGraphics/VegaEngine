#pragma once
#include "VegaEngine2.h"

namespace fz {

	class SceneSerializer
	{
	public:
		SceneSerializer(const Shared<Scene>& scene);

		void Serialize(const std::string& path);
		void SerializeRuntime(const std::string& path);

		bool Deserialize(const std::string& path);
		bool DeserializeRuntime(const std::string& path);

	private:
		Shared<Scene> m_Scene;
	};

} // namespace 