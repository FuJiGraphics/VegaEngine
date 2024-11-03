#pragma once

namespace fz {

	class Scene
	{
	protected:
		using Super = fz::Scene;
		FZ_DELETE_COPY(Scene)

	public:
		Scene();
		~Scene();


	private:
		entt::registry	m_Registry;
	};

} // namespace fz