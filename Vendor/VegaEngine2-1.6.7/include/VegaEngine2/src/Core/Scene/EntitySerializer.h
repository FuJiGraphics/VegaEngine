#pragma once
#include "Entity.h"

namespace fz {

	class EntitySerializer
	{
	public:
		EntitySerializer(const std::string& sceneUUID, const fz::Entity& entity);

		void Serialize(const std::string& path);
		void Deserialize(const std::string& path);

	protected:
		void SerializeTag(json& json);
		void SerializeCamera(json& json);
		void SerializeTransform(json& json);
		void SerializeSprite(json& json);

		void DeserializeTag(json& json);
		void DeserializeCamera(json& json);
		void DeserializeTransform(json& json);
		void DeserializeSprite(json& json);

		template<typename T>
		T& FindComponent()
		{
			if (!m_Entity.HasComponent<T>())
				return m_Entity.AddComponent<T>();
			else
				return m_Entity.GetComponent<T>();
		}

	private:
		fz::Entity m_Entity;
		std::string m_SceneUUID;
		std::string m_EntityUUID;
	};

} // namespace fz