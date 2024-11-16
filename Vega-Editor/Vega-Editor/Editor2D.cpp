#include "Editor2D.h"

namespace fz {
	Editor2D::Editor2D(const std::string& name)
		: Layer(name)
		, texId(0)
		, m_ActiveScene(nullptr)
		, m_SquareEntity()
		, m_CameraEntity()
		, m_HierarchyPanel(m_ActiveScene)
	{

	}

	void Editor2D::OnAttach()
	{
		FZLOG_INFO("Editor2D 시작");
		TEXTURE_MGR.Load("graphics/player.png");

		m_ActiveScene = CreateShared<Scene>(1024, 768);
		//// Entity
		//m_SquareEntity = m_ActiveScene->CreateEntity("Player");
		//auto& spriteComp = m_SquareEntity.AddComponent<SpriteComponent>();
		//spriteComp.Sprite.SetTexture("graphics/player.png");

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
		auto& camera = m_CameraEntity.AddComponent<CameraComponent>(sf::Vector2f{ 0.0f, 0.0f }, sf::Vector2f{ 1024.f, 768.f });
		camera.Primary = true;

	} /// OnAttach

	void Editor2D::OnDetach()
	{
		FZLOG_INFO("Editor2D 종료");
		TEXTURE_MGR.Unload("Graphics/player.png");
		texId = 0;
	}

	void Editor2D::OnUpdate(float dt)
	{
		if (m_ActiveScene)
			m_ActiveScene->OnUpdate(dt);
	}

	void Editor2D::OnEvent(fz::Event& ev)
	{

	}

	void Editor2D::OnUI()
	{
		ImGui::BeginMainMenuBar();
		auto nativeWindow = (sf::RenderWindow*)System::GetSystem().GetWindow().GetNativeWindow();
		HWND handle = (HWND)nativeWindow->getSystemHandle();

		if (ImGui::BeginMenu("File"))
		{
			

			if (ImGui::MenuItem("New", "Ctrl+N"))
			{


			}
			if (ImGui::MenuItem("Open...", "Ctrl+O"))
			{
				std::string path = VegaUI::OpenFile(handle, "Scene File (*.json)\0*.json\0");
				SceneSerializer serializer;
				m_ActiveScene = serializer.Deserialize(path);
				if (!m_ActiveScene)
				{
					m_ActiveScene = CreateShared<Scene>(1024, 768);
					m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
					auto& camera = m_CameraEntity.AddComponent<CameraComponent>(sf::Vector2f{ 0.0f, 0.0f }, sf::Vector2f{ 1024.f, 768.f });
					camera.Primary = true;
				}
				m_HierarchyPanel.SetContext(m_ActiveScene);

				// TODO: Test
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

				if (m_ActiveScene)
				{
					m_CameraEntity = m_ActiveScene->GetEntityFromTag("Camera");
					if (m_CameraEntity)
						m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
				}
			}

			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
			{
				std::string path = VegaUI::SaveFile(handle, "Scene File (*.json)\0*.json\0");
				SceneSerializer serializer(m_ActiveScene);
				serializer.Serialize(path);
			}

			if (ImGui::MenuItem("Exit"))
			{
				System::GetSystem().ExitSystem();
			}

			ImGui::EndMenu();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		if (ImGui::Begin("Viewport"))
		{
			if (m_ActiveScene)
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
		}
		// Viewport End
		ImGui::End();
		ImGui::PopStyleVar();

		m_HierarchyPanel.OnImGuiRender();

		ImGui::EndMainMenuBar();
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