#pragma once

#include "Core/Core.h"
#include "entt/entt.hpp"
#include "Scene.h"

namespace fz {

	class Entity 
	{
	public:
		Entity();
		Entity(entt::entity handle, const Shared<Scene>& scene);
		Entity(const Entity& other);
		Entity(Entity&& other) noexcept;

		Entity& operator=(const Entity& other);
		Entity& operator=(Entity&& other);

		template <typename T, typename ...Args>
		T& AddComponent(Args&&... args)
		{
			(!HasComponent<T>(), "엔티티에 동일한 컴포넌트가 이미 존재합니다.");
			return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
		}

		template <typename T>
		void RemoveComponent()
		{
			FZLOG_ASSERT(HasComponent<T>(), "엔티티에서 제거하려는 컴포넌트를 찾을 수 없습니다.");
			m_Scene->m_Registry.remove<T>(m_Handle);
		}

		template <typename T>
		T& GetComponent()
		{
			FZLOG_ASSERT(HasComponent<T>(), "컴포넌트를 찾을 수 없습니다.");
			return m_Scene->m_Registry.get<T>(m_Handle);
		}

		template <typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_Handle);
		}

		operator bool() const { return m_Handle != entt::null; }

	private:
		entt::entity	m_Handle;
		Weak<Scene>		m_Scene;
	};

} // namespace fz