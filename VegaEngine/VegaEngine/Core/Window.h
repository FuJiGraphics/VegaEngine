#pragma once
#include "Core.h"
#include "Core/Event/EventList.h"

namespace fz {

	struct WindowInfo
	{
		int Width;
		int Height;
		std::string Title;
	};

	class Window
	{
	//// Delete, Enum, Using
	protected:
		// Delete
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

	//// Member Functions
	public:
		// Constructor, Destructor
		Window();
		virtual ~Window();

		// Impl
		void Create(int width, int height, const std::string& title);
		void Release();
		void Event(EventList& events);

		// Inlines
		inline bool IsOpen() const								{ return m_IsOpen; }
		inline sf::RenderWindow& GetRenderWindow()				{ return (*m_NativeWindow); }
		inline sf::RenderWindow& GetRenderWindow() const		{ return (*m_NativeWindow); }
		inline sf::RenderTexture& GetFrameBuffer()				{ return m_FrameBuffer; }
		inline const sf::RenderTexture& GetFrameBuffer() const	{ return m_FrameBuffer; }

	//// Member Variables
	private:
		WindowInfo m_Info;
		sf::RenderTexture m_FrameBuffer;
		sf::RenderWindow* m_NativeWindow;
		bool m_IsOpen;
	};

} // namespace fz

