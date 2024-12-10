#include "pch.h"
#include "WindowSFML.h"

namespace fz {

	WindowSFML::WindowSFML(const fz::WindowMode& mode)
		: m_Window(nullptr)
		, m_Mode(mode)
		, m_CallbackFn(nullptr)
		, m_IsVSync(mode.VSync)
	{
		FZLOG_INFO("WindowSFML ��ü ���� ��..");
	}

	WindowSFML::~WindowSFML()
	{
		FZLOG_INFO("WindowSFML ��ü ���� ��..");
	}

	void WindowSFML::Init()
	{
		FZLOG_INFO("Window �ʱ�ȭ ��..");
		m_Window = std::make_unique<sf::RenderWindow>();
		sf::VideoMode mode;
		mode.width = m_Mode.Width;
		mode.height = m_Mode.Height;
		FZLOG_INFO("-------------- # Window SFML ���� ���� # -------------");
		FZLOG_INFO("- Title: {0}", m_Mode.Title);
		FZLOG_INFO("- Width: {0}, Height: {1}", m_Mode.Width, m_Mode.Height);
		FZLOG_INFO("- VSync Ȱ��ȭ ����: {0}", m_IsVSync);
		FZLOG_INFO("- Antialiasing Level: {0}", m_Mode.AntialiasingLevel);
		FZLOG_INFO("------------------------------------------------------");
		sf::ContextSettings context;
		context.antialiasingLevel = m_Mode.AntialiasingLevel;
		m_Window->create(mode, m_Mode.Title, sf::Style::Default, context);
		m_Window->setVerticalSyncEnabled(m_IsVSync);
		FZLOG_INFO("Window �ʱ�ȭ �Ϸ�");
	}

	void WindowSFML::Release()
	{
		FZLOG_INFO("WindowSFML ���ҽ� ���� ��..");
		if (m_Window != nullptr)
		{
			m_Window->close();
			FZLOG_INFO("WindowSFML ���ҽ� ���� �Ϸ�");
		}
	}

	void WindowSFML::OnEvent()
	{
		static int s_RepeatCount = 0;
		static bool s_RepeatOn = false;
		sf::Event input;
		while (m_Window->pollEvent(input))
		{
			ImGuiManager::PollEvent(input);
			InputManager::PollEvent(input);
			switch (input.type)
			{
				case sf::Event::Closed: {
					if (m_CallbackFn) 
					{
						WindowCloseEvent event;
						m_CallbackFn(event);
					}
					else
					{
						m_Window->close();
					}
				} break;
				case sf::Event::Resized: {
					if (m_CallbackFn)
					{
						auto size = m_Window->getSize();
						m_Mode.Width = size.x;
						m_Mode.Height = size.y;
						WindowResizeEvent event(m_Mode.Width, m_Mode.Height);
						m_CallbackFn(event);
					}
				} break;
				case sf::Event::KeyPressed: {
					if (m_CallbackFn) {
						if (s_RepeatOn == false)
						{
							s_RepeatOn = true;
							s_RepeatCount = 0;
						}
						else
							s_RepeatCount++;
						KeyPressedEvent event((int)input.key.code, s_RepeatCount);
						m_CallbackFn(event);
					}
				} break;
				case sf::Event::KeyReleased: {
					if (m_CallbackFn) {
						s_RepeatOn = false;
						s_RepeatCount = 0;
						KeyReleasedEvent event(input.key.code);
						m_CallbackFn(event);
					}
				} break;
				case sf::Event::MouseButtonPressed: {
					if (m_CallbackFn) {
						MouseButtonPressedEvent event(Converter::SfmlToFzType(input.mouseButton.button));
						m_CallbackFn(event);
					}
				} break;
				case sf::Event::MouseButtonReleased: {
					if (m_CallbackFn) {
						MouseButtonReleasedEvent event(Converter::SfmlToFzType(input.mouseButton.button));
						m_CallbackFn(event);
					}
				} break;
				case sf::Event::MouseWheelScrolled: {
					if (m_CallbackFn) {
						if (input.mouseWheelScroll.wheel == sf::Mouse::Wheel::VerticalWheel) {
							MouseScrolledEvent event(0.0f, input.mouseWheelScroll.delta);
							m_CallbackFn(event);
						}
						else {
							MouseScrolledEvent event(input.mouseWheelScroll.delta, 0.0f);
							m_CallbackFn(event);
						}
					}
				} break;
				case sf::Event::MouseMoved: {
					if (m_CallbackFn) {
						MouseMovedEvent event((float)input.mouseMove.x, (float)input.mouseMove.y);
						m_CallbackFn(event);
					}
				} break;
			}
		}
	} // WindowSFML::OnEvent()

	void WindowSFML::OnUpdate()
	{
		m_Window->display();
		m_Window->clear();
	}

	int WindowSFML::GetWidth() const
	{
		return m_Mode.Width;
	}

	int WindowSFML::GetHeight() const
	{
		return m_Mode.Height;
	}

	std::string WindowSFML::GetTitle() const
	{
		return m_Mode.Title;
	}

	void* WindowSFML::GetNativeWindow() const
	{
		return m_Window.get();
	}

	HWND WindowSFML::GetHandle() const
	{
		return m_Window->getSystemHandle();
	}

	bool WindowSFML::IsFocus() const
	{
		return m_Window->hasFocus();
	}

	bool WindowSFML::IsVSync() const
	{
		return m_IsVSync;
	}

	bool WindowSFML::IsOpen() const
	{
		return m_Window->isOpen();
	}

	void WindowSFML::SetTitle(const std::string& title)
	{
		m_Window->setTitle(title);
	}

	void WindowSFML::ActivateOpenGL(bool enabled)
	{
		if (enabled)
			m_Window->popGLStates();
		else
			m_Window->pushGLStates();

		FZLOG_ASSERT(m_Window->setActive(enabled), "OpenGL Ȱ��ȭ�� �� �� ���� ������ �߻��߽��ϴ�.");
	}

	void WindowSFML::SetVSync(bool enabled)
	{
		m_IsVSync = enabled;
		m_Window->setVerticalSyncEnabled(enabled);
	}

	void WindowSFML::SetEventCallback(const EventCallbackFn& callback)
	{
		FZLOG_INFO("Window Callback Function ���� ��..");
		m_CallbackFn = callback;
	}

} // namespace fz