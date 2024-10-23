#include "Core/stdafx.h"
#include "System.h"
#include "Window.h"
#include "Framework/ResourceManager.h"
#include "Platform/ImGui/ImGuiManager.h"
#include "Event/EventList.h"
#include "Framework/SceneManager.h"

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
	}

	void System::Release()
	{
		Texture::UnloadAll();
		Font::UnloadAll();
		if (m_Window != nullptr)
		{
			SceneManager::Release();
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
			SceneManager::Event(eventQueue);

			// Layer 업데이트
			SceneManager::Update(dt.asSeconds());

			// 충돌 체크

			// 모든 오브젝트 그리기
			m_Window->Begin();
			SceneManager::Draw(*m_Window);

			// ImGui
			ImGuiManager::Begin(dt);
			m_Window->Render();
			ImGuiManager::ShowDemo();
			ImGuiManager::End();
			m_Window->End();
		}
		m_IsClosed = true;
	}

} // namespace fz



