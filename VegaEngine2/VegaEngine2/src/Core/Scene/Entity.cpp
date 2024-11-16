#include "pch.h"
#include "Entity.h"

namespace fz {
	Entity::Entity()
		: m_Handle{ entt::null }
		, m_Scene(nullptr)
		, m_UUID(Random.GetUUID())
	{
		// Empty
	}

	Entity::Entity(entt::entity handle, const Shared<Scene>& scene)
		: m_Handle(handle)
		, m_Scene(scene)
		, m_UUID(Random.GetUUID())
	{
		// Empty
	}

	Entity::Entity(const std::string& uuid, entt::entity handle, const Shared<Scene>& scene)
		: m_Handle(handle)
		, m_Scene(scene)
		, m_UUID(uuid)
	{
		// Empty
	}

	Entity::Entity(const Entity& other)
		: m_Handle(other.m_Handle)
		, m_Scene(other.m_Scene)
		, m_UUID(other.m_UUID)
	{
		// Empty
	}

	Entity::Entity(Entity&& other) noexcept
		: m_Handle(other.m_Handle)
		, m_Scene(other.m_Scene)
		, m_UUID(other.m_UUID)
	{
		other.m_Handle = entt::null;
		other.m_Scene = nullptr;
		other.m_UUID = "";
	}

	Entity& Entity::operator=(const Entity& other)
	{
		this->m_Handle = other.m_Handle;
		this->m_Scene = other.m_Scene;
		this->m_UUID = other.m_UUID;
		return *this;
	}

	Entity& Entity::operator=(Entity&& other)
	{
		this->m_Handle = other.m_Handle;
		this->m_Scene = other.m_Scene;
		this->m_UUID = other.m_UUID;
		other.m_Handle = entt::null;
		other.m_Scene = nullptr;
		other.m_UUID = "";
		return *this;
	}

} // namespace fz