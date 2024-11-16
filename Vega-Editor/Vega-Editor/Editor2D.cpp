#include "Editor2D.h"

namespace fz {
	Editor2D::Editor2D(const std::string& name)
		: Layer(name)
		, texId(0)
		, m_SquareEntity()
		, m_CameraEntity()
		, m_HierarchyPanel(m_ActiveScene)
	{

	}

	void Editor2D::OnAttach()
	{
		FZLOG_INFO("Editor2D 시작");
		TEXTURE_MGR.Load("graphics/player.png");

		m_ActiveScene = LoadScene("json/scenes.json");
		m_HierarchyPanel.SetContext(m_ActiveScene);
		//m_ActiveScene = CreateShared<Scene>(1024, 768);
		//// Entity
		//m_SquareEntity = m_ActiveScene->CreateEntity("Player");
		//auto& spriteComp = m_SquareEntity.AddComponent<SpriteComponent>();
		//spriteComp.Sprite.SetTexture("graphics/player.png");

		//m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
		//auto& camera = m_CameraEntity.AddComponent<CameraComponent>(sf::Vector2f{ 0.0f, 0.0f }, sf::Vector2f{ 1024.f, 768.f });
		//camera.Primary = true;

		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
				auto& transform = GetComponent<TransformComponent>();
				transform.Transform.SetTranslate(0.0f, 0.0f);
			}

			void OnDestroy()
			{

			}

			void OnUpdate(float dt)
			{
				auto& transformComponent = GetComponent<TransformComponent>();
				auto& transform = transformComponent.Transform;
				auto prevPos = transform.GetTranslate();
				if (InputManager::IsKeyPressed(KeyType::W))
				{
					prevPos.y -= m_Speed * dt;
					transform.SetTranslate(prevPos);
				}
				if (InputManager::IsKeyPressed(KeyType::S))
				{
					prevPos.y += m_Speed * dt;
					transform.SetTranslate(prevPos);
				}
				if (InputManager::IsKeyPressed(KeyType::A))
				{
					prevPos.x -= m_Speed * dt;
					transform.SetTranslate(prevPos);
				}
				if (InputManager::IsKeyPressed(KeyType::D))
				{
					prevPos.x += m_Speed * dt;
					transform.SetTranslate(prevPos);
				}
			};
		private:
			float m_Speed = 100.f;
		};

		m_CameraEntity = m_ActiveScene->GetEntityFromTag("Camera");
		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
	} /// OnAttach

	void Editor2D::OnDetach()
	{
		FZLOG_INFO("Editor2D 종료");
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
			auto& frameBuffer = m_ActiveScene->GetFrameBuffer();
			ImGui::Image(*frameBuffer);
			if (vpSize.x > 0.0f && vpSize.y > 0.0f &&
				frameBuffer->GetWidth() != (unsigned int)vpSize.x || frameBuffer->GetHeight() != (unsigned int)vpSize.y)
			{
				m_ActiveScene->OnViewportResize((unsigned int)vpSize.x, (unsigned int)vpSize.y);
			}
		}
		// Viewport End
		ImGui::End();
		ImGui::PopStyleVar();

		// TODO: 테스트
		if (ImGui::Button("SaveScene"))
		{
			this->SaveScene(m_ActiveScene);
		}

		m_HierarchyPanel.OnImGuiRender();
	}

	void Editor2D::SaveScene(const Shared<Scene>& scene)
	{
		// TODO: 테스트
		SceneSerializer serializer(scene);
		serializer.Serialize("json/scenes.json");
	}

	Shared<Scene> Editor2D::LoadScene(const std::string& path)
	{
		// TODO: 테스트
		SceneSerializer serializer(nullptr);
		return serializer.Deserialize(path);
	}

} // namespace fz