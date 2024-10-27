#include "pch.h"
#include "System.h"

namespace fz { 

	System::System(int width, int height, const std::string& title)
		: IsOpen(true)
		, Width(width)
		, Height(height)
		, Title(title)
		, m_Window(nullptr)
		, m_ObjectStack(nullptr)
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
		else 
		{
			result = this->GenerateWindow();
			if (result)
				result = this->GenerateObjectStack();

		}
		if (result)
			Log.Trace("System �ʱ�ȭ �Ϸ�");
		else
			Log.Error("System �ʱ�ȭ ����");
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
			Log.Error("System ���� ����");
		return result;
	}

	bool System::Reset()
	{
		bool result = true;
		Log.Trace("System ����");

		if (result)
			Log.Trace("System ���� �Ϸ�");
		else
			Log.Error("System ���� ����");
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
			Log.Trace("Object ���� ����");
			m_ObjectStack = CreateShared<ObjectStack>();
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
