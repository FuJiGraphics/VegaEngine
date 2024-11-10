#pragma once

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

		Shared<Framebuffer>& GetFrameBuffer();
		const Shared<Framebuffer>& GetFrameBuffer() const;

	private:
		entt::registry		m_Registry;
		Shared<Framebuffer>	m_FrameBuffer;
	};

} // namespace fz