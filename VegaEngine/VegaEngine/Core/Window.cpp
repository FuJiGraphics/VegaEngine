#include "Core/stdafx.h"
#include "Event/Event.h"
#include "Window.h"

namespace fz {

	Window::Window()
		: m_Info({ 0, 0, "" })
		, m_Camera()
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
		m_Camera.create(width, height);
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
			m_Camera.clear();
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
				case sf::Event::Closed:
					m_IsOpen = false;
					break;
				case sf::Event::GainedFocus:
					break;
				default:
					events.push_back(fz::Event(ev));
			}
		}
	}

	void Window::Display()
	{
		m_Camera.clear();
		m_NativeWindow->clear();
	}

	void Window::Begin()
	{
	}

	void Window::End()
	{
		m_NativeWindow->display();
	}

	void Window::Render()
	{
		sf::Sprite sprite(m_Camera.getTexture());
		m_NativeWindow->draw(sprite);
		m_Camera.display();
		m_NativeWindow->clear();
		ImGui::Begin("Scene");
		ImVec2 windowSize = ImGui::GetContentRegionAvail();
		ImGui::Image(m_Camera.getTexture().getNativeHandle(), windowSize, {0.0f, 1.0f}, {1.0f, 0.0f});
		ImGui::End();
	}

} // namespace fz