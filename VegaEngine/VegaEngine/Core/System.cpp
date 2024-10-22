#include "Core/stdafx.h"
#include "System.h"
#include "Window.h"
#include "LayerArray.h"
#include "ColliderManager.h"
#include "Framework/ResourceManager.h"
#include "Platform/ImGui/ImGuiManager.h"

namespace fz {

	float	System::s_timeScale = 1.0f;

	System& System::GetInstance()
	{
		static	System	s_system;
		return (s_system);
	}

	void System::AttachLayer(Layer* pLayer)
	{
		System& system = System::GetInstance();
		system.m_layerArray->InsertLayer(pLayer);
		pLayer->OnAttach();
	}

	void System::AttachOverlay(Layer* pOverlay)
	{
		System& system = System::GetInstance();
		system.m_layerArray->InsertOverlay(pOverlay);
		pOverlay->OnAttach();
	}

	void System::DetachLayer(Layer* pLayer)
	{
		System& system = System::GetInstance();
		system.m_layerArray->RemoveLayer(pLayer);
		pLayer->OnDetach();
	}

	void System::DetachOverlay(Layer* ppOverlay)
	{
		System& system = System::GetInstance();
		system.m_layerArray->RemoveOverlay(ppOverlay);
		ppOverlay->OnDetach();
	}

	Layer* System::FindLayer(const std::string& className)
	{
		System& system = System::GetInstance();
		Layer* target = nullptr;
		for (auto layer : *system.m_layerArray)
		{
			if (className == layer->GetName())
			{
				target = layer;
				break;
			}
		}
		return (target);
	}

	void System::ExitProgram()
	{
		System& system = System::GetInstance();
		system.m_isPlaying = false;
		system.m_isReset = false;
	}

	void System::SetPause(bool enabled)
	{
		System& system = System::GetInstance();
		system.m_isPause = enabled;
		s_timeScale = (enabled) ? 0.0f : 1.0f;
	}

	void System::SetReset(bool enabled)
	{
		System& system = System::GetInstance();
		system.m_isPlaying = (enabled) ? false : true;
		system.m_isReset = enabled;
	}

	bool System::IsReset()
	{
		System& system = System::GetInstance();
		return (system.m_isReset);
	}

	bool System::IsPaused()
	{
		System& system = System::GetInstance();
		return (system.m_isPause);
	}

	void System::Init(const WindowInfo& info)
	{
		if (m_window != nullptr)
			return;

		m_window = new Window(info.Width, info.Height, info.Title.c_str());
		m_window->Create();
		m_width = info.Width;
		m_height = info.Height;

		m_RenderTarget.create(m_width, m_height);

		ImGuiManager::Init(*m_window);
	}

	void System::Run()
	{
		sf::Clock clock;
		while (m_isPlaying && m_window->IsOpen())
		{
			EventQueue eventQueue;
			sf::Time dt = clock.restart();
			s_timeScale = (m_isPause) ? 0.0f : 1.0f;

			// 레이어 추가 요청 처리
			m_layerArray->WorkingInsertLayers();

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
			auto& colManager = ColliderManager::GetInstance();
			for (auto collider1 : colManager)
			{
				for (auto collider2 : colManager)
				{
					(*collider1)->IsCollided(**collider2);
				}
			}

			// 삭제 요청된 레이어 정리
			m_layerArray->WorkingGarbage();

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
		if (!m_isReset)
			return;

		s_timeScale = 1.0f;
		m_isPlaying = true;
		m_isPause = false;
		m_isReset = false;
		this->ReleaseLayerArray();
		this->CreateLayerArray();
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



