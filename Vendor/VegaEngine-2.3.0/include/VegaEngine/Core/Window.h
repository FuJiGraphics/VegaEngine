#pragma once
#include "Core.h"
#include "EventQueue.h"

namespace fz {

	class Window
	{
	public:
		Window(int width, int height, const char* name);
		virtual ~Window();

		void				Create();
		void				Release();
		bool				IsOpen();
		void				Event(EventQueue* dst);
		sf::RenderWindow&	GetHandle();
		sf::RenderWindow&	GetHandle() const;

	private:
		int					m_width;	// 윈도우의 너비
		int					m_height;	// 윈도우의 높이
		std::string			m_name;		// 윈도우의 이름
		sf::RenderWindow*	m_hwnd;		// 핸들
		bool				m_isOpen;	// 윈도우 활성화 여부
	};

} // namespace fz

