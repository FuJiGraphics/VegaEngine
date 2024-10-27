#include "pch.h"
#include "System.h"

namespace fz { 

	System::System(int width, int height, const std::string& title)
		: IsOpen(true)
		, m_Window(nullptr)
		, Width(width)
		, Height(height)
		, Title(title)
	{
		// Empty
	}

	System::~System()
	{
		// Empty
	}

	bool System::Init()
	{
		bool result = true;
		Log.Trace("System 초기화");
		if (Width <= 0 || Height <= 0)
		{
			Log.Error("윈도우 생성 인자 오류 width = {0}, height = {1}", Width, Height);
			result = false;
		}
		else {
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
			m_Window = Window::Create(winMode);
			m_Window->SetEventCallback(BIND_EVENT_FUNC(System::OnEvent));
			if (m_Window == nullptr)
			{
				Log.Error("윈도우 생성중 문제를 알 수 없는 오류가 발생했습니다.");
			}
			Log.Trace("Window 초기화 중");
			m_Window->Init();
			Log.Trace("Window 초기화 완료");
			Log.Trace("Window 생성 완료");
			// ...
		}
		if (result)
			Log.Trace("System 초기화 완료");
		else
			Log.Trace("System 초기화 실패");
		return result;
	}

	bool System::Release()
	{
		bool result = true;
		Log.Trace("System 해제");
		// Window
		{ 
			Log.Trace("Window 해제 중");
			m_Window->Release();
			Log.Trace("Window 해제 완료");
		}
		if (result)
			Log.Trace("System 해제 완료");
		else
			Log.Trace("System 해제 실패");
		return result;
	}

	bool System::Reset()
	{
		bool result = true;
		Log.Trace("System 리셋");

		if (result)
			Log.Trace("System 해제 완료");
		else
			Log.Trace("System 해제 실패");
		return result;
	}

	void System::Run()
	{
		Log.Trace("System Run...");

		while (m_Window->IsOpen())
		{
			m_Window->OnEvent();



			m_Window->OnUpdate();
		}
		Log.Trace("System Run Off");
	}

	void System::OnEvent(fz::Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(System::OnWindowClose));
	}

	bool System::OnWindowClose(WindowCloseEvent e)
	{
		m_Window->Release();
		return true;
	}

} // namespace fz
