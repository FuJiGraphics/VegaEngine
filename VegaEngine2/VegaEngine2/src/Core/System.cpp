#include "pch.h"
#include "System.h"

namespace fz { 

	System::System(int width, int height, const std::string& title)
		: IsInit(false)
		, IsOpen(true)
		, Width(width)
		, Height(height)
		, Title(title)
		, m_Window(nullptr)
		, m_ObjectStack(nullptr)
		, ObjectGenerator(nullptr)
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
				result = this->GenerateObjectStack();
			ImGuiManager::Init(*m_Window);
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
		// Release ObjectStack
		{
			this->ReleaseObjectStack();
		}
		// Window
		{ 
			Log.Trace("Window ���� ��");
			m_Window->Release();
			Log.Trace("Window ���� �Ϸ�");
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
		this->ReleaseObjectStack();

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

			// Update
			for (Object* obj : *m_ObjectStack)
			{
				if (obj != nullptr)
				{
					obj->OnUpdate(dt);
				}
			}

			// ImGui
			ImGuiManager::Begin(t);
			{
				ImGuiManager::ShowDemo();
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
		for (Object* obj : *m_ObjectStack)
		{
			if (obj != nullptr)
			{
				obj->OnEvent(e);
			}
		}
	}

	void System::PushObject(Object* object)
	{
		m_ObjectStack->PushObject(object);
	}

	void System::PushOverlay(Object* overlay)
	{
		m_ObjectStack->PushObject(overlay);
	}

	bool System::OnWindowClose(WindowCloseEvent e)
	{
		m_Window->Release();
		return true;
	}

	bool System::GenerateWindow()
	{
		Log.Trace("Window ����");
		bool result = true;
		WindowMode winMode;
		winMode.Width = Width;
		winMode.Height = Height;
		winMode.Title = Title;
		winMode.Api = WindowAPI::SFML;
		std::string api = {};
		if (winMode.Api == WindowAPI::SFML)
			api = "SFML";
		else if (winMode.Api == WindowAPI::GLFW)
			api = "GLFW";
		Log.Trace("Window ���� �ɼ� width = {0}, height = {1}, title = {2}, API = {3}",
			Width, Height, Title, api
		);

		Log.Trace("Window ��ü ���� ��");
		m_Window = Window::Create(winMode);
		if (m_Window != nullptr)
		{
			Log.Trace("Window �ݹ� �Լ� ��� ��");
			m_Window->SetEventCallback(BIND_EVENT_FUNC(System::OnEvent));

			Log.Trace("Window �ʱ�ȭ ��");
			m_Window->Init();
			Log.Trace("Window �ʱ�ȭ �Ϸ�");
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

	bool System::GenerateObjectStack()
	{
		bool result = true;
		if (m_ObjectStack && m_ObjectStack->size() > 0)
		{
			Log.Warn("Object ������ �̹� ���� �Ǿ� �ֽ��ϴ�.");
			result = false;
		}
		else 
		{
			Log.Trace("Object Pool ����");
			ObjectGenerator = CreateShared<ObjectPool>();
			Log.Trace("Object ���� ����");
			m_ObjectStack = CreateShared<ObjectStack>(ObjectGenerator);
			if (m_ObjectStack == nullptr)
				result = false;
		}
		if (result)
			Log.Trace("Object ���� ���� �Ϸ�");
		else
			Log.Error("Object ���� ���� ����");
		return result;
	}

	bool System::ReleaseObjectStack()
	{
		bool result = true;
		Log.Trace("Object ���� ����");
		m_ObjectStack->Release();

		if (result)
			Log.Trace("Object ���� ���� �Ϸ�");
		else
			Log.Error("Object ���� ���� ����");
		return result;
	}

} // namespace fz
