#include "Core/stdafx.h"
#include "System.h"
#include "Window.h"
#include "Framework/ResourceManager.h"
#include "Platform/ImGui/ImGuiManager.h"

namespace fz {

	void System::Create(int width, int height, const std::string& title)
	{
		this->Release();
		m_Window = new Window();
			m_RenderTarget.create(m_width, m_height);

		ImGuiManager::Init(*m_window);
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
		while (m_isPlaying && m_window->IsOpen())
		{
			sf::Time dt = clock.restart();
			s_timeScale = (m_isPause) ? 0.0f : 1.0f;

			// 이벤트 루프
			m_window->Event(&eventQueue);

			// Layer 이벤트 전송
			eventQueue.DispatchTo(*m_layerArray);

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
			for (auto layer : (*m_layerArray))
			{
				layer->OnUI(m_RenderTarget);
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
		: m_window(nullptr)
		, m_width(0)
		, m_height(0)
		, m_layerArray(nullptr)
		, m_isPlaying(true)
		, m_isPause(false)
		, m_isReset(false)
	{
		this->CreateLayerArray();
	}

	System::~System()
	{
		ImGuiManager::Shutdown();
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



