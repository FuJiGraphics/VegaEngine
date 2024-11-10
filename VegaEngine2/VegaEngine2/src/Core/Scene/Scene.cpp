#include "pch.h"
#include "Scene.h"
#include "Entity.h"

namespace fz {
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& tagName)
	{
		Entity entity = { m_Registry.create(), shared_from_this() };
		auto& tagComp = entity.AddComponent<TagComponent>(tagName);
		if (tagComp.Tag.empty())
			tagComp.Tag = "Entity";

		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::OnUpdate(float dt)
	{
	}

} // namespace fz