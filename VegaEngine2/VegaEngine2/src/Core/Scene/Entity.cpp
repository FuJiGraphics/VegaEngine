#include "pch.h"
#include "Entity.h"

namespace fz {
	Entity::Entity()
		: m_Handle{ 0 }
		, m_Scene(nullptr)
	{
		// Empty
	}

	Entity::Entity(entt::entity handle, const Shared<Scene>& scene)
		: m_Handle(handle)
		, m_Scene(scene)
	{
		// Empty
	}

	Entity::Entity(const Entity& other)
		: m_Handle(other.m_Handle)
		, m_Scene(other.m_Scene)
	{
		// Empty
	}

	Entity::Entity(Entity&& other) noexcept
		: m_Handle(other.m_Handle)
		, m_Scene(other.m_Scene)
	{
		other.m_Handle = entt::entity{ 0 };
		other.m_Scene = nullptr;
	}

	Entity& Entity::operator=(const Entity& other)
	{
		this->m_Handle = other.m_Handle;
		this->m_Scene = other.m_Scene;
		return *this;
	}

	Entity& Entity::operator=(Entity&& other)
	{
		this->m_Handle = other.m_Handle;
		this->m_Scene = other.m_Scene;
		other.m_Handle = entt::entity{ 0 };
		other.m_Scene = nullptr;
		return *this;
	}

} // namespace fz