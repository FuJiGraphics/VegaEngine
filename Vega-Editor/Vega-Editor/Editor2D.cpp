#include "Editor2D.h"

namespace fz {
	Editor2D::Editor2D(const std::string& name)
		: Layer(name)
		, m_ActiveScene(nullptr)
		, m_SceneState(EditorState::Edit)
		, m_HierarchyPanel(m_ActiveScene, &m_SceneState)
		, m_EditorCamera({ (float)FRAMEWORK.GetWidth(), (float)FRAMEWORK.GetHeight() }, false)
	{
		// Empty
	}

	void Editor2D::OnAttach()
	{
		FZLOG_INFO("Editor2D ����");
		TEXTURE_MGR.Load("graphics/player.png");
		TEXTURE_MGR.Load("editor/icons/playbutton.png");
		TEXTURE_MGR.Load("editor/icons/stopbutton.png");
		if (Utils::CanFileOpen(g_TempProjectPath))
			m_ActiveScene = LoadScene(g_TempProjectPath);
		if (m_ActiveScene == nullptr)
			m_ActiveScene = CreateScene(FRAMEWORK.GetWidth(), FRAMEWORK.GetHeight());
		m_HierarchyPanel.SetContext(m_ActiveScene, &m_SceneState);
		SpriteEditor::SetContext(m_ActiveScene);
		Scene::s_CurrentScene = m_ActiveScene;
	}

	void Editor2D::OnDetach()
	{
		FZLOG_INFO("Editor2D ����");
		TEXTURE_MGR.Unload("Graphics/player.png");
		TEXTURE_MGR.Unload("editor/icons/playbutton.png");
		TEXTURE_MGR.Unload("editor/icons/stopbutton.png");
	}

	void Editor2D::OnUpdate(float dt)
	{
		switch (m_SceneState)
		{
			case EditorState::Edit:
				m_ActiveScene->OnUpdateEditor(dt, m_EditorCamera);
				SpriteEditor::OnUpdate(dt);
				break;
			case EditorState::Play:
				m_ActiveScene->OnUpdate(dt);
				break;
		}
	}

	void Editor2D::OnEvent(fz::Event& ev)
	{
		if (m_SceneState == EditorState::Edit)
		{
			m_EditorCamera.OnEvent(ev);
			SpriteEditor::OnEvent(ev);
		}
	}

	void Editor2D::OnUI()
	{
		ImGui::BeginMainMenuBar();
		auto nativeWindow = (sf::RenderWindow*)System::GetSystem().GetWindow().GetNativeWindow();
		HWND handle = (HWND)nativeWindow->getSystemHandle();

		// ���� �� Ű
		if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && ImGui::IsKeyPressed(ImGuiKey_S))
		{
			if (m_SceneState == EditorState::Edit)
			{
				SaveScene(m_ActiveScene, m_ActiveSceneFilePath);
				FZLOG_INFO("Scene Save UUID = {0}", m_ActiveScene->GetUUID());
			}
		}

		if (ImGui::BeginMenu("File"))
		{
			if (m_SceneState == EditorState::Edit && ImGui::MenuItem("New", "Ctrl+N"))
			{
				m_ActiveScene = CreateScene(FRAMEWORK.GetWidth(), FRAMEWORK.GetHeight());
				m_HierarchyPanel.SetContext(m_ActiveScene, &m_SceneState);
				m_ActiveSceneFilePath.clear();
				this->OnScenePlay();
				this->OnSceneStop();
			}
			if (m_SceneState == EditorState::Edit && ImGui::MenuItem("Open...", "Ctrl+O"))
			{
				this->OnSceneStop();
				std::string prevPath = m_ActiveSceneFilePath;
				m_ActiveSceneFilePath = VegaUI::OpenFile(handle, "Scene File (*.vega)\0*.vega\0");
				if (m_ActiveSceneFilePath.empty())
				{
					m_ActiveSceneFilePath = prevPath;
				}
				else if (!m_ActiveSceneFilePath.empty())
				{
					m_ActiveScene = LoadScene(m_ActiveSceneFilePath);
				}
				if (!m_ActiveScene)
					m_ActiveScene = CreateScene(FRAMEWORK.GetWidth(), FRAMEWORK.GetHeight());
				m_HierarchyPanel.SetContext(m_ActiveScene, &m_SceneState);
			}
			if (m_SceneState == EditorState::Edit && ImGui::MenuItem("Save", "Ctrl+S"))
			{
				if (!m_ActiveSceneFilePath.empty()) 
				{
					SaveScene(m_ActiveScene, m_ActiveSceneFilePath);
				}
				else
				{
					std::string path = VegaUI::SaveFile(handle, "Scene File (*.vega)\0*.vega\0");
					SaveScene(m_ActiveScene, path);
				}
			}
			if (m_SceneState == EditorState::Edit && ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
			{
				std::string path = VegaUI::SaveFile(handle, "Scene File (*.vega)\0*.vega\0");
				if (!path.empty())
				{
					SaveScene(m_ActiveScene, path);
				}
			}
			if (m_SceneState == EditorState::Edit && ImGui::MenuItem("Exit"))
			{
				System::GetSystem().ExitSystem();
			}
			ImGui::EndMenu();

			Scene::s_CurrentScene = m_ActiveScene;
		}

		if (ImGui::BeginMenu("Tools"))
		{
			if (ImGui::MenuItem("Sprite Editor"))
			{
				SpriteEditor::SetActive(true);
			}
			ImGui::EndMenu();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		if (ImGui::Begin("Viewports"))
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
			// ���콺 �̵� ��� ����
			if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) && ImGui::IsWindowFocused())
				m_EditorCamera.SetActivated(true);
			else
				m_EditorCamera.SetActivated(false);
		}
		// Viewport End
		ImGui::End();
		ImGui::PopStyleVar();

		this->UiToolbar();
		m_HierarchyPanel.OnImGuiRender();
		if (ImGui::Begin("Draw Debug Mode"))
		{
			if (m_ActiveScene)
			{
				bool flag = m_ActiveScene->IsDebugDisplayMode();
				if (ImGui::Checkbox("##debugMode", &flag))
				{
					m_ActiveScene->SetDebugDisplayMode(flag);
				}
			}
		}
		ImGui::End(); // Viewports

		SpriteEditor::OnUI();

		ImGui::EndMainMenuBar();
	}

	Shared<Scene> Editor2D::CreateScene(unsigned int width, unsigned int height)
	{
		Shared<Scene> newScene = CreateShared<Scene>(width, height);
		return newScene;
	}

	void Editor2D::SaveScene(const Shared<Scene>& scene, const std::string& path)
	{
		SceneSerializer serializer(scene);
		serializer.Serialize(path);
	}

	Shared<Scene> Editor2D::LoadScene(const std::string& path)
	{
		SceneSerializer serializer(nullptr);
		Shared<Scene> loadScene = serializer.Deserialize(path);
		return loadScene;
	}

	void Editor2D::OnScenePlay()
	{
		m_SceneState = EditorState::Play;
		SaveScene(m_ActiveScene, g_TempProjectPath);
		auto loadScene = LoadScene(g_TempProjectPath);
		if (loadScene)
			m_ActiveScene = loadScene;
		m_HierarchyPanel.SetContext(m_ActiveScene, &m_SceneState);
		this->BindScript();
		m_ActiveScene->OnPreUpdate();
	}

	void Editor2D::OnSceneStop()
	{
		m_SceneState = EditorState::Edit;
		m_ActiveScene->OnPostUpdate();
		if (!m_ActiveSceneFilePath.empty())
		{
			m_ActiveScene = LoadScene(m_ActiveSceneFilePath);
			m_HierarchyPanel.SetContext(m_ActiveScene, &m_SceneState);
		}
	}

	void Editor2D::UiToolbar(const char* title)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		auto& colors = ImGui::GetStyle().Colors;
		const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
		const auto& buttonActive = colors[ImGuiCol_ButtonActive];
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

		ImGuiWindowFlags flag = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
		if (ImGui::Begin(title, nullptr, flag))
		{
			float size = ImGui::GetWindowHeight() - 4.0f;
			ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
			if (ImGui::ImageButton("##PlayButton", TEXTURE_MGR.Get("editor/icons/PlayButton.png"), {size, size}))
			{
				if (m_SceneState == EditorState::Edit)
					OnScenePlay();
			}
			ImGui::SameLine();
			if (ImGui::ImageButton("##StopButton", TEXTURE_MGR.Get("editor/icons/StopButton.png"), { size, size }))
			{
				if (m_SceneState == EditorState::Play)
					OnSceneStop();
			}
		}
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(3);
		ImGui::End();
	}

	void Editor2D::BindScript()
	{
		auto& base = BindScriptBase::GetInstance();
		for (auto& script : base)
		{
			std::string sceneUUID = m_ActiveScene->GetUUID();
			script->Bind(sceneUUID, m_ActiveScene);
		}
	}

} // namespace fz