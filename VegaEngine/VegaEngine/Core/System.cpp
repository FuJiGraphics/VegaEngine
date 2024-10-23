#include "Core/stdafx.h"
#include "System.h"
#include "Window.h"
#include "Framework/ResourceManager.h"
#include "Platform/ImGui/ImGuiManager.h"
#include "Event/EventList.h"

namespace fz {

	System::System()
		: m_Window(nullptr)
		, m_IsPause(false)
		, m_IsClosed(false)
		, m_TimeScale(1.0f)
	{
		// Empty
	}

	System::~System()
	{
		this->Release();
	}

	void System::Create(int width, int height, const std::string& title)
	{
		this->Release();
		m_Window = new Window();
		m_Window->Create(width, height, title);
		m_SceneList = new SceneList();
		m_SceneList->InsertScene("1");
	}

	void System::Release()
	{
		if (m_Window != nullptr)
		{
			m_Window->Release();
			delete m_Window;
			m_Window = nullptr;
		}
	}

	void System::Run()
	{
		sf::Clock clock;
		while (m_Window->IsOpen())
		{
			sf::Time dt = clock.restart();
			m_TimeScale = (m_IsPause) ? 0.0f : 1.0f;

			EventList eventQueue;
			// 이벤트 루프
			m_Window->Event(eventQueue);
			m_SceneList->Event(eventQueue);

			// Layer 업데이트
			m_SceneList->Update(dt.asSeconds());

			// 충돌 체크

			// 모든 오브젝트 그리기
			m_Window->Begin();
			m_SceneList->Draw(*m_Window);

			// ImGui
			ImGuiManager::Begin(dt);
			ImGuiManager::ShowDemo();
			m_Window->Render();
			ImGuiManager::End();
			m_Window->End();
		}
		m_IsClosed = true;
	}

} // namespace fz



