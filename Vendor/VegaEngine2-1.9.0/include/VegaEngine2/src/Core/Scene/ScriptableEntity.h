#pragma once
#include "Entity.h"
#include "Scene.h"

namespace fz {

	class ScriptableEntity
	{
	public:
		template <typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

		template <typename T>
		bool HasComponent()
		{
			return m_Entity.HasComponent<T>();
		}

	private:
		Entity m_Entity;

		friend fz::Scene;
	};

} // namespace fz
