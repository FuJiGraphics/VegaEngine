#pragma once

#include "Core/Core.h"
#include "entt/entt.hpp"
#include "Scene.h"

namespace fz {

	class EntitySerializer;
	class HierarchyPanel;

	class Entity 
	{
	protected:
		friend fz::Scene;
		friend fz::EntitySerializer;
		friend fz::SceneSerializer;
		friend fz::HierarchyPanel;

	public:
		Entity();
		Entity(entt::entity handle, const Shared<Scene>& scene);
		Entity(const std::string& uuid, entt::entity handle, const Shared<Scene>& scene);
		Entity(const Entity& other);
		Entity(Entity&& other) noexcept;

		template <typename T, typename ...Args>
		T& AddComponent(Args&&... args)
		{
			FZLOG_ASSERT(m_Handle != entt::null, "��ƼƼ�� �������� �ʽ��ϴ�.");
			bool result = !HasComponent<T>();
			FZLOG_ASSERT(result, "��ƼƼ�� ������ ������Ʈ�� �̹� �����մϴ�.");
			return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
		}

		template <typename T>
		void RemoveComponent()
		{
			FZLOG_ASSERT(m_Handle != entt::null, "��ƼƼ�� �������� �ʽ��ϴ�.");
			FZLOG_ASSERT(HasComponent<T>(), "��ƼƼ���� �����Ϸ��� ������Ʈ�� ã�� �� �����ϴ�.");
			m_Scene->m_Registry.remove<T>(m_Handle);
		}

		template <typename T>
		T& GetComponent()
		{
			FZLOG_ASSERT(m_Handle != entt::null, "��ƼƼ�� �������� �ʽ��ϴ�.");
			FZLOG_ASSERT(HasComponent<T>(), "������Ʈ�� ã�� �� �����ϴ�.");
			return m_Scene->m_Registry.get<T>(m_Handle);
		}

		template <typename T>
		bool HasComponent()
		{
			FZLOG_ASSERT(m_Handle != entt::null, "��ƼƼ�� �������� �ʽ��ϴ�.");
			return m_Scene->m_Registry.all_of<T>(m_Handle);
		}

		template <typename T>
		bool HasComponent() const
		{
			FZLOG_ASSERT(m_Handle != entt::null, "��ƼƼ�� �������� �ʽ��ϴ�.");
			return m_Scene->m_Registry.all_of<T>(m_Handle);
		}

		inline bool operator ==(const fz::Entity& other) const	{ return m_Handle == other.m_Handle && m_Scene == other.m_Scene; }
		inline bool operator !=(const fz::Entity& other) const	{ return !((*this) == other); }
		inline operator bool() const							{ return m_Handle != entt::null; }
		inline operator std::uint32_t() const					{ return (std::uint32_t)m_Handle; }

		Entity& operator=(const Entity& other);
		Entity& operator=(Entity&& other);

	protected:
		fz::Entity CreateChildEntity(const std::string& uuid, const std::string& tagName);
		void SavePrefab(const std::string& path);
		void LoadPrefab(const std::string& path);
		void SetActiveWithChild(bool enabled);

	private:
		entt::entity	m_Handle;
		Weak<Scene>		m_Scene;
		std::string		m_UUID;
	};

	using GameObject = fz::Entity;

} // namespace fz