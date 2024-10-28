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
		Log.Trace("System 초기화");
		if (Width <= 0 || Height <= 0)
		{
			Log.Error("윈도우 생성 인자 오류 width = {0}, height = {1}", Width, Height);
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
			Log.Trace("System 초기화 완료");
		else
			Log.Error("System 초기화 실패");
		IsInit = result;
		return result;
	}

	bool System::Release()
	{
		if (!IsInit)
			return false;

		bool result = true;
		Log.Trace("System 해제");
		// Release ObjectStack
		{
			this->ReleaseObjectStack();
		}
		// Window
		{ 
			Log.Trace("Window 해제 중");
			m_Window->Release();
			Log.Trace("Window 해제 완료");
		}
		// ImGui
		{
			ImGuiManager::Release();
		}
		if (result)
			Log.Trace("System 해제 완료");
		else
			Log.Error("System 해제 실패");
		IsInit = !result;
		return result;
	}

	bool System::Reset()
	{
		bool result = true;
		Log.Trace("System 리셋");
		this->ReleaseObjectStack();

		if (result)
			Log.Trace("System 해제 완료");
		else
			Log.Error("System 해제 실패");
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
		Log.Trace("Window 생성");
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
		Log.Trace("Window 생성 옵션 width = {0}, height = {1}, title = {2}, API = {3}",
			Width, Height, Title, api
		);

		Log.Trace("Window 객체 생성 중");
		m_Window = Window::Create(winMode);
		if (m_Window != nullptr)
		{
			Log.Trace("Window 콜백 함수 등록 중");
			m_Window->SetEventCallback(BIND_EVENT_FUNC(System::OnEvent));

			Log.Trace("Window 초기화 중");
			m_Window->Init();
			Log.Trace("Window 초기화 완료");
		}
		else
		{
			Log.Error("윈도우 생성중 문제를 알 수 없는 오류가 발생했습니다.");
			result = false;
		}
		if (result)
			Log.Trace("Window 생성 완료");
		else
			Log.Error("Window 생성 실패");
		return result;
	}

	bool System::GenerateObjectStack()
	{
		bool result = true;
		if (m_ObjectStack && m_ObjectStack->size() > 0)
		{
			Log.Warn("Object 스택이 이미 생성 되어 있습니다.");
			result = false;
		}
		else 
		{
			Log.Trace("Object Pool 생성");
			ObjectGenerator = CreateShared<ObjectPool>();
			Log.Trace("Object 스택 생성");
			m_ObjectStack = CreateShared<ObjectStack>(ObjectGenerator);
			if (m_ObjectStack == nullptr)
				result = false;
		}
		if (result)
			Log.Trace("Object 스택 생성 완료");
		else
			Log.Error("Object 스택 생성 실패");
		return result;
	}

	bool System::ReleaseObjectStack()
	{
		bool result = true;
		Log.Trace("Object 스택 해제");
		m_ObjectStack->Release();

		if (result)
			Log.Trace("Object 스택 해제 완료");
		else
			Log.Error("Object 스택 해제 실패");
		return result;
	}

} // namespace fz
