#include "pch.h"
#include "System.h"

namespace fz { 

	System::System(int width, int height, const std::string& title)
		: IsInit(false)
		, IsOpen(true)
		, Width(width)
		, Height(height)
		, Title(title)
		, LayerGenerator(nullptr)
		, m_LayerStack(nullptr)
		, m_Window(nullptr)
		, m_RenderContext(nullptr)
	{
		this->Init();
	}

	System::~System()
	{
		this->Release();
	}

	bool System::Init()
	{
		if (IsInit)
			return false;

		bool result = true;
		Log.Trace("System �ʱ�ȭ");
		if (Width <= 0 || Height <= 0)
		{
			Log.Error("������ ���� ���� ���� width = {0}, height = {1}", Width, Height);
			result = false;
		}
		else 
		{
			result = this->GenerateWindow();
			if (result)
				result = this->GenerateLayerStack();
			ImGuiManager::Init(*m_Window);
			InputManager::SetTargetTrackingWindow((sf::RenderWindow*)m_Window->GetNativeWindow());
			Renderer2D::Init((sf::RenderWindow*)m_Window->GetNativeWindow());
		}
		if (result)
			Log.Trace("System �ʱ�ȭ �Ϸ�");
		else
			Log.Error("System �ʱ�ȭ ����");
		IsInit = result;
		return result;
	}

	bool System::Release()
	{
		if (!IsInit)
			return false;

		bool result = true;
		Log.Trace("System ����");
		// Release LayerStack
		{
			this->ReleaseLayerStack();
		}
		// Window
		{ 
			m_Window->Release();
		}
		// ImGui
		{
			ImGuiManager::Release();
		}
		if (result)
			Log.Trace("System ���� �Ϸ�");
		else
			Log.Error("System ���� ����");
		IsInit = !result;
		return result;
	}

	bool System::Reset()
	{
		bool result = true;
		Log.Trace("System ����");
		this->ReleaseLayerStack();

		if (result)
			Log.Trace("System ���� �Ϸ�");
		else
			Log.Error("System ���� ����");
		return result;
	}

	void System::Run()
	{
		Log.Trace("System Run...");
		sf::Clock clock;

		while (m_Window->IsOpen())
		{
			sf::Time t = clock.restart();
			float dt = t.asSeconds();
			// Event
			m_Window->OnEvent();
			if (!m_Window->IsOpen())
				continue;

			// Update
			for (Layer* obj : *m_LayerStack)
			{
				if (obj != nullptr)
				{
					obj->OnUpdate(dt);
				}
			}

			// ImGui
			ImGuiManager::Begin(t);
			{
				for (Layer* obj : *m_LayerStack)
				{
					if (obj != nullptr)
					{
						obj->OnUI();
					}
				}
			}
			ImGuiManager::End();

			m_Window->OnUpdate();
		}
		Log.Trace("System Run Off");
	}

	void System::OnEvent(fz::Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(System::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(System::OnWindowResize));
		for (Layer* obj : *m_LayerStack)
		{
			if (obj != nullptr)
			{
				obj->OnEvent(e);
			}
		}
	}

	void System::PushLayer(Layer* layer)
	{
		m_LayerStack->PushLayer(layer);
	}

	void System::PushOverlay(Layer* overlay)
	{
		m_LayerStack->PushLayer(overlay);
	}

	bool System::OnWindowClose(WindowCloseEvent e)
	{
		m_Window->Release();
		return true;
	}

	bool System::OnWindowResize(WindowResizeEvent e)
	{ 
		return true;
	}

	bool System::GenerateWindow()
	{
		bool result = true;
		WindowMode winMode;
		winMode.Width = Width;
		winMode.Height = Height;
		winMode.Title = Title;
		winMode.Api = WindowAPI::SFML;
		winMode.VSync = true;
		m_Window = Window::Create(winMode);
		if (m_Window != nullptr)
		{
			m_Window->SetEventCallback(BIND_EVENT_FUNC(System::OnEvent));
			m_Window->Init(m_RenderContext);
		}
		else
		{
			Log.Error("������ ������ ������ �� �� ���� ������ �߻��߽��ϴ�.");
			result = false;
		}
		if (result)
			Log.Trace("Window ���� �Ϸ�");
		else
			Log.Error("Window ���� ����");
		return result;
	}

	bool System::GenerateLayerStack()
	{
		bool result = true;
		if (m_LayerStack && m_LayerStack->size() > 0)
		{
			Log.Warn("Layer ������ �̹� ���� �Ǿ� �ֽ��ϴ�.");
			result = false;
		}
		else 
		{
			Log.Trace("Layer Pool ����");
			LayerGenerator = CreateShared<LayerPool>();
			Log.Trace("Layer ���� ����");
			m_LayerStack = CreateShared<LayerStack>(LayerGenerator);
			if (m_LayerStack == nullptr)
				result = false;
		}
		if (result)
			Log.Trace("Layer ���� ���� �Ϸ�");
		else
			Log.Error("Layer ���� ���� ����");
		return result;
	}

	bool System::ReleaseLayerStack()
	{
		bool result = true;
		Log.Trace("Layer ���� ����");
		m_LayerStack->Release();

		if (result)
			Log.Trace("Layer ���� ���� �Ϸ�");
		else
			Log.Error("Layer ���� ���� ����");
		return result;
	}

} // namespace fz
