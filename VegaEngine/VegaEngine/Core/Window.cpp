#include "Core/stdafx.h"
#include "Window.h"
#include <SFML/Window.hpp>

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

		if (ImGui::SFML::Init(*m_NativeWindow))
		{
			// std::cout << "¼º°ø!" << std::endl;
		}
		m_IsOpen = true;
	}

	void Window::Release()
	{
		if (m_NativeWindow != nullptr)
		{
			ImGui::SFML::Shutdown();
			delete m_NativeWindow;
			m_FrameBuffer.clear();
			m_NativeWindow = nullptr;
			m_Info = { 0, 0, "" };
			m_IsOpen = false;
		}
	}

	void Window::Event(EventManager& manager)
	{
		if (!m_IsOpen)
			return;

		sf::Event ev;
		while (m_NativeWindow->pollEvent(ev))
		{
			ImGui::SFML::ProcessEvent(*m_NativeWindow, ev);
			switch (ev.type)
			{
				case sf::Event::GainedFocus:
				case sf::Event::Closed:
					m_IsOpen = false;
					break;
				default:
					manager.pollEvent(ev);
			}
		}
	}

} // namespace fz