#pragma once

namespace fz {
	
	// Forwards
	class Entity;

	class Scene : public std::enable_shared_from_this<Scene>
	{
	protected:
		using Super = fz::Scene;
		FZ_DELETE_COPY(Scene)
		friend fz::Entity;

	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& tagName = std::string());
		
		void OnUpdate(float dt);

	private:
		entt::registry	m_Registry;
	};

} // namespace fz