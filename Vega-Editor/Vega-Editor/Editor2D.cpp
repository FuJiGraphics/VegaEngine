#include "Editor2D.h"

namespace fz {
	Editor2D::Editor2D(const std::string& name)
		: Layer(name)
		, texId(0)
		, m_SquareEntity()
		, m_CameraEntity()
	{
	}

	void Editor2D::OnAttach()
	{
		Log.Info("Editor2D 시작");
		TEXTURE_MGR.Load("graphics/player.png");

		m_ActiveScene = CreateShared<Scene>(1024, 768);

		// Entity
		m_SquareEntity = m_ActiveScene->CreateEntity("Square");
		sf::Sprite& sprite = m_SquareEntity.AddComponent<SpriteComponent>();
		sprite.setTexture(TEXTURE_MGR.Get("graphics/player.png"));
		sprite.setPosition(0.0f, 0.0f);

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
		m_CameraEntity.AddComponent<CameraComponent>(sf::Vector2f{ 0.0f, 0.0f }, sf::Vector2f{ 1024.f, 768.f });
	}

	void Editor2D::OnDetach()
	{
		Log.Info("Editor2D 종료");
		TEXTURE_MGR.Unload("Graphics/player.png");
		texId = 0;
	}

	void Editor2D::OnUpdate(float dt)
	{
		m_ActiveScene->OnUpdate(dt);
	}

	void Editor2D::OnEvent(fz::Event& ev)
	{

	}

	void Editor2D::OnUI()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		if (ImGui::Begin("Viewport"))
		{
			ImVec2 vpSize = ImGui::GetContentRegionAvail();

			static float f[2] = { vpSize.x, vpSize.y };
			ImGui::DragFloat2("Viewport Resize", f);
			vpSize.x = f[0];
			vpSize.y = f[1];
			auto& frameBuffer = m_ActiveScene->GetFrameBuffer();
			ImGui::Image(*frameBuffer);
			if (vpSize.x > 0.0f && vpSize.y > 0.0f &&
				frameBuffer->GetWidth() != (unsigned int)vpSize.x || frameBuffer->GetHeight() != (unsigned int)vpSize.y)
			{
				m_ActiveScene->OnViewportResize((unsigned int)vpSize.x, (unsigned int)vpSize.y);
			}

			ImGuiManager::ShowDemo();

			ImGui::Begin("Position");
			sf::Sprite& sprite = m_SquareEntity.GetComponent<SpriteComponent>();
			auto spritePos = sprite.getPosition();
			ImGui::DragFloat("x", &spritePos.x);
			ImGui::DragFloat("y", &spritePos.y);
			sprite.setPosition(spritePos);
			ImGui::End();

			ImGui::Begin("Camera A");
			fz::Transform& transform = m_CameraEntity.GetComponent<TransformComponent>();
			sf::Vector2f translate = transform.GetTranslate();
			ImGui::DragFloat("x", &translate.x);
			ImGui::DragFloat("y", &translate.y);
			transform.SetTranslate(translate);
			ImGui::End();

		}
		// Viewport End
		ImGui::End();
		ImGui::PopStyleVar();
	}

} // namespace fz