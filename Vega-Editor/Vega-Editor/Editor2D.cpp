#include "Editor2D.h"

namespace fz {
	Editor2D::Editor2D(const std::string& name)
		: Layer(name)
		, m_ActiveScene(nullptr)
		, m_HierarchyPanel(m_ActiveScene)
	{

	}

	void Editor2D::OnAttach()
	{
		FZLOG_INFO("Editor2D 시작");
		TEXTURE_MGR.Load("graphics/player.png");
		m_ActiveScene = CreateScene(FRAMEWORK.GetWidth(), FRAMEWORK.GetHeight());
		m_HierarchyPanel.SetContext(m_ActiveScene);
	}

	void Editor2D::OnDetach()
	{
		FZLOG_INFO("Editor2D 종료");
		TEXTURE_MGR.Unload("Graphics/player.png");
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
				m_ActiveScene = CreateScene(FRAMEWORK.GetWidth(), FRAMEWORK.GetHeight());
				m_HierarchyPanel.SetContext(m_ActiveScene);
			}
			if (ImGui::MenuItem("Open...", "Ctrl+O"))
			{
				Shared<Scene> prevScene = m_ActiveScene;
				m_ActiveSceneFilePath = VegaUI::OpenFile(handle, "Scene File (*.json)\0*.json\0");
				if (m_ActiveSceneFilePath.empty())
					m_ActiveScene = prevScene;
				else
				{
					m_ActiveScene = LoadScene(m_ActiveSceneFilePath);
					if (!m_ActiveScene)
						m_ActiveScene = CreateScene(FRAMEWORK.GetWidth(), FRAMEWORK.GetHeight());
				}
				m_HierarchyPanel.SetContext(m_ActiveScene);
			}
			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{
				SaveScene(m_ActiveScene, m_ActiveSceneFilePath);
			}
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
			{
				std::string path = VegaUI::SaveFile(handle, "Scene File (*.json)\0*.json\0");
				SaveScene(m_ActiveScene, path);
			}
			if (ImGui::MenuItem("Exit"))
			{
				System::GetSystem().ExitSystem();
			}
			ImGui::EndMenu();

			Scene::s_CurrentScene = m_ActiveScene;
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
		auto& base = BindScriptBase::GetInstance();
		for (auto& script : base)
		{
			script->Bind(loadScene->GetUUID(), loadScene);
		}
		return loadScene;
	}

} // namespace fz