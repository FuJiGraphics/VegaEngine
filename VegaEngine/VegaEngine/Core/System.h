#pragma once
#include "Core.h"

namespace fz {

	class Window;

	struct WindowInfo
	{
		int Width;
		int Height;
		std::string Title;
	};

	class System
	{	
	//// Delete, Enum, Using
	protected:
		// Delete
		System(const System&) = delete;
		System& operator=(const System&) = delete;

	//// Member Functions
	public:
		// Constructor, Destructor
		System();
		virtual ~System();

		// Impl
		void Create(int width, int height, const std::string& title);
		void Release();
		void Run();

	//// Member Variables
	private:
		Window* m_Window;
		WindowInfo m_Info;
		sf::RenderTexture m_RenderTarget;
		float m_TimeScale;
	};

} // namespace fz