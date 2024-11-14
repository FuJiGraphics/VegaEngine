#pragma once
#include "Renderer/FrameBuffer.h"

namespace fz {
	
	// Forwards
	class Entity;
	class Framebuffer;

	class Scene : public std::enable_shared_from_this<Scene>
	{
	protected:
		using Super = fz::Scene;
		FZ_DELETE_COPY(Scene)
		friend fz::Entity;

	public:
		Scene(unsigned int width, unsigned int height, unsigned int mulltisampleLevel = 1);
		~Scene();

		Entity CreateEntity(const std::string& tagName = std::string());
		
		void OnUpdate(float dt);
		void OnViewportResize(unsigned int width, unsigned int height);

		inline sf::Vector2u GetViewportSize() const { return { m_FrameBuffer->GetWidth(), m_FrameBuffer->GetHeight() }; }
		inline Shared<Framebuffer>& GetFrameBuffer() { return m_FrameBuffer; }
		inline const Shared<Framebuffer>& GetFrameBuffer() const { return m_FrameBuffer; }

	private:
		entt::registry		m_Registry;
		Shared<Framebuffer>	m_FrameBuffer;
	};

} // namespace fz