#include "Core/stdafx.h"
#include "System.h"
#include "Window.h"
#include "Framework/ResourceManager.h"
#include "Platform/ImGui/ImGuiManager.h"
#include "Event/EventList.h"

namespace fz {

	void System::Create(int width, int height, const std::string& title)
	{
		this->Release();
		m_Window = new Window();
		m_Window->Create(width, height, title);
	}

	void System::Create(const WindowInfo& info)
	{
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

			// Layer 업데이트
			for (auto layer : (*m_layerArray))
			{
				layer->OnUpdate(dt.asSeconds());
			}

			// 충돌 체크

			// 모든 오브젝트 그리기
			m_RenderTarget.clear(sf::Color::Red);
			for (auto layer : (*m_layerArray))
			{
				layer->OnDraw(m_RenderTarget);
			}
			for (auto collider : colManager)
			{
				if ((*collider)->IsDisplay())
				{
					auto& rect = (*collider)->GetBox();
					m_RenderTarget.draw(rect);
				}
			}

			m_RenderTarget.display();
			m_window->GetHandle().clear();

			sf::Sprite sprite(m_RenderTarget.getTexture());
			m_window->GetHandle().draw(sprite);

			// ImGui
			ImGuiManager::Begin(dt);
			ImGui::Begin("Scene");
			ImGuiManager::ShowDemo();
			ImVec2 windowSize = ImGui::GetContentRegionAvail();
			ImGui::Image(m_RenderTarget.getTexture().getNativeHandle(), windowSize, { 0.0f, 1.0f }, {1.0f, 0.0f});
			ImGui::End();
			for (auto layer : (*m_layerArray))
			{
				layer->OnImGui();
			}
			ImGuiManager::End();
			// End the current frame and display its contents on screen
			m_window->GetHandle().display();
		}
	}

	void System::Reset()
	{
		fz::Texture::UnloadAll();
		fz::Font::UnloadAll();
	}

	int System::GetWidth()
	{
		return (m_width);
	}

	int System::GetHeight()
	{
		return (m_height);
	}

	System::System()
		: m_Window(nullptr)
		, m_IsPause(false)
		, m_TimeScale(1.0f)
	{
		// Empty
	}

	System::~System()
	{
		ReleaseWindow();
		ReleaseLayerArray();
	}

	void System::ReleaseWindow()
	{
		if (m_window != nullptr)
		{
			m_window->Release();
			delete m_window;
			m_window = nullptr;
		}
	}

	void System::CreateLayerArray()
	{
		if (m_layerArray != nullptr)
			return;
		
		m_layerArray = new LayerList();
	}

	void System::ReleaseLayerArray()
	{
		if (m_layerArray != nullptr)
		{
			delete m_layerArray;
			m_layerArray = nullptr;
		}
	}

} // namespace fz



