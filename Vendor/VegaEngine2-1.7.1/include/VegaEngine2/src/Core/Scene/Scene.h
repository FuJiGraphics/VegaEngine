#pragma once
#include "Renderer/FrameBuffer.h"
#include "SceneSerializer.h"

namespace fz {
	
	// Forwards
	class Entity;
	class Framebuffer;
	class HierarchyPanel;
	class SceneSerializer;

	class Scene : public std::enable_shared_from_this<Scene>
	{
	protected:
		using Super = fz::Scene;
		using EntityPool = std::unordered_map<std::string, entt::entity>;
		FZ_DELETE_COPY(Scene)
		friend fz::Entity;
		friend fz::HierarchyPanel;
		friend fz::SceneSerializer;

	public:
		Scene(unsigned int width, unsigned int height, unsigned int mulltisampleLevel = 1, const std::string& uuid = "");
		~Scene();

		Entity CreateEntity(const std::string& tagName = "");
		Entity CreateEntity(const std::string& uuid, const std::string& tagName);
		void DeleteEntity(fz::Entity& entity);
		
		void OnUpdate(float dt);
		void OnViewportResize(unsigned int width, unsigned int height);

		Entity GetEntityFromUUID(const std::string& uuid);
		Entity GetEntityFromTag(const std::string& tag);
		inline sf::Vector2u GetViewportSize() const { return { m_FrameBuffer->GetWidth(), m_FrameBuffer->GetHeight() }; }
		inline Shared<Framebuffer>& GetFrameBuffer() { return m_FrameBuffer; }
		inline const Shared<Framebuffer>& GetFrameBuffer() const { return m_FrameBuffer; }

	private:
		entt::registry			m_Registry;
		Shared<Framebuffer>		m_FrameBuffer;
		std::string				m_UUID;
		EntityPool				m_EntityPool;
	};

} // namespace fz