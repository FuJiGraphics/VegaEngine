#pragma once
#include "Renderer/FrameBuffer.h"
#include "SceneSerializer.h"

class b2WorldId;

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
		friend fz::Entity;
		friend fz::HierarchyPanel;
		friend fz::SceneSerializer;
		FZ_DELETE_COPY(Scene)

	public:
		Scene(unsigned int width, unsigned int height, unsigned int mulltisampleLevel = 1, const std::string& uuid = "");
		~Scene();

		Entity CreateEntity(const std::string& tagName = "");
		Entity CreateEntityWithUUID(const std::string& tagName, const std::string& uuid);
		Entity CreateEntity(const std::string& uuid, const std::string& tagName);
		void DeleteEntity(fz::Entity& entity);
		
		void OnUpdate(float dt);
		void OnViewportResize(unsigned int width, unsigned int height);

		Entity GetEntityFromUUID(const std::string& uuid);
		Entity GetEntityFromTag(const std::string& tag);
		inline sf::Vector2u GetViewportSize() const { return { m_FrameBuffer->GetWidth(), m_FrameBuffer->GetHeight() }; }
		inline Shared<Framebuffer>& GetFrameBuffer() { return m_FrameBuffer; }
		inline const Shared<Framebuffer>& GetFrameBuffer() const { return m_FrameBuffer; }

		// TODO: 임시
		std::string GetUUID() const { return m_UUID; }

	public:
		// TODO: 임시
		inline static Weak<Scene>	s_CurrentScene;

	private:
		entt::registry			m_Registry;
		Shared<Framebuffer>		m_FrameBuffer;
		std::string				m_UUID;
		EntityPool				m_EntityPool;
		b2WorldId*				m_World;
	};

#define FZ_CURRENT_SCENE Scene::s_CurrentScene

} // namespace fz