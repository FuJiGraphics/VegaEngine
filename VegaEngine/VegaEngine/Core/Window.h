#pragma once
#include "Core.h"

namespace fz {

	class EventManager;

	struct WindowInfo
	{
		int Width;
		int Height;
		std::string Title;
	};

	class Window
	{
	public:
		Window();
		virtual ~Window();

		void Create(int width, int height, const std::string& title);
		void Release();
		void Event(EventManager& manager);

		bool IsOpen() const							{ return m_IsOpen; }
		sf::RenderWindow& GetRenderWindow()			{ return (*m_NativeWindow); }
		sf::RenderWindow& GetRenderWindow() const	{ return (*m_NativeWindow); }

	private:
		WindowInfo m_Info;
		sf::RenderTexture m_FrameBuffer;
		sf::RenderWindow* m_NativeWindow;
		bool m_IsOpen;
	};

} // namespace fz

