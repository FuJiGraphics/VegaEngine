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
		Log.Trace("System �ʱ�ȭ");
		if (Width <= 0 || Height <= 0)
		{
			Log.Error("������ ���� ���� ���� width = {0}, height = {1}", Width, Height);
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
			Log.Trace("Window ���� �ɼ� width = {0}, height = {1}, title = {2}, API = {3}",
				Width, Height, Title, api
			);
			m_Window = Window::Create(winMode);
			m_Window->SetEventCallback(BIND_EVENT_FUNC(System::OnEvent));
			if (m_Window == nullptr)
			{
				Log.Error("������ ������ ������ �� �� ���� ������ �߻��߽��ϴ�.");
			}
			Log.Trace("Window �ʱ�ȭ ��");
			m_Window->Init();
			Log.Trace("Window �ʱ�ȭ �Ϸ�");
			Log.Trace("Window ���� �Ϸ�");
			// ...
		}
		if (result)
			Log.Trace("System �ʱ�ȭ �Ϸ�");
		else
			Log.Trace("System �ʱ�ȭ ����");
		return result;
	}

	bool System::Release()
	{
		bool result = true;
		Log.Trace("System ����");
		// Window
		{ 
			Log.Trace("Window ���� ��");
			m_Window->Release();
			Log.Trace("Window ���� �Ϸ�");
		}
		if (result)
			Log.Trace("System ���� �Ϸ�");
		else
			Log.Trace("System ���� ����");
		return result;
	}

	bool System::Reset()
	{
		bool result = true;
		Log.Trace("System ����");

		if (result)
			Log.Trace("System ���� �Ϸ�");
		else
			Log.Trace("System ���� ����");
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
