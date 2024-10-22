#pragma once

#include "Core/Core.h"
#include "Core/Window.h"

namespace fz {

	class ImGuiManager
	{
	public:
		static bool			Init(const fz::Window& window);
		static void			Shutdown();
		static void			SetWindow(const fz::Window& window);
		static void			Begin(const sf::Time& dt);
		static void			End();
		static void			ShowDemo();

	private:
		static bool					s_enableOverviewDockspace;
		static const fz::Window*	s_currWindow;
	};

} // namespace fz