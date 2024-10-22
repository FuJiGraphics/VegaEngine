#include "Core/stdafx.h"
#include "Window.h"

namespace fz {

	Window::Window()
		: m_Info({ 0, 0, "" })
		, m_FrameBuffer()
		, m_NativeWindow(nullptr)
		, m_IsOpen(false)
	{
		// Empty
	}

	Window::~Window()
	{
		this->Release();
	}

	void Window::Create(int width, int height, const std::string& title)
	{
		this->Release();
		m_Info = { width, height, title };

		sf::VideoMode mode(width, height);
		m_FrameBuffer.create(width, height);
		m_NativeWindow = new sf::RenderWindow(mode, title);

		if (ImGuiManager::Init(*this))
		{
			// std::cout << "¼º°ø!" << std::endl;
		}
		m_IsOpen = true;
	}

	void Window::Release()
	{
		if (m_NativeWindow != nullptr)
		{
			ImGuiManager::Shutdown();
			delete m_NativeWindow;
			m_FrameBuffer.clear();
			m_NativeWindow = nullptr;
			m_Info = { 0, 0, "" };
			m_IsOpen = false;
		}
	}

	void Window::Event(EventList& events)
	{
		if (!m_IsOpen)
			return;

		sf::Event ev;
		while (m_NativeWindow->pollEvent(ev))
		{
			ImGuiManager::PollEvent(ev);
			switch (ev.type)
			{
				case sf::Event::GainedFocus:
				case sf::Event::Closed:
					m_IsOpen = false;
					break;
				default:
					events.push_back(ev);
			}
		}
	}

} // namespace fz