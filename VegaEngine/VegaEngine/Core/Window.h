#pragma once
#include "Core.h"
#include "Core/Event/EventList.h"
#include "Core/Camera/Camera.h"

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
		void Display();
		void Begin();
		void End();
		void Render();

		// Inlines
		inline bool IsOpen() const								{ return m_IsOpen; }
		inline sf::RenderWindow& GetRenderWindow()				{ return (*m_NativeWindow); }
		inline sf::RenderWindow& GetRenderWindow() const		{ return (*m_NativeWindow); }
		inline sf::RenderTexture& GetFrameBuffer()				{ return m_Camera; }
		inline const sf::RenderTexture& GetFrameBuffer() const	{ return m_Camera; }
		inline Camera& GetCamera()								{ return m_Camera; }
		inline const Camera& GetCamera() const					{ return m_Camera; }

	//// Member Variables
	private:
		WindowInfo m_Info;
		Camera m_Camera;
		sf::RenderWindow* m_NativeWindow;
		bool m_IsOpen;
		sf::Sprite m_Sprite;
	};

} // namespace fz

