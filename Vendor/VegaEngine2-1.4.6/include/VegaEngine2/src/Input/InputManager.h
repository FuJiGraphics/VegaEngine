#pragma once

#include "Core/Core.h"

namespace sf {
	class WindowBase;
}

namespace fz {

	class InputManager
	{
	public:
		inline static bool IsKeyPressed(KeyType keycode) {
			return InputManager::IsKeyPressedImpl(keycode); 
		}
		inline static bool IsMouseButtonPressed(MouseButtonType button) {
			return InputManager::IsMouseButtonPressedImpl(button);
		}
		inline static sf::Vector2f GetMousePosition() {
			return InputManager::GetMousePositionImpl();
		}
		inline static void SetTargetTrackingWindow(sf::WindowBase* window) {
			s_TargetWindow = window;
		}

	protected:
		static bool IsKeyPressedImpl(KeyType keycode);
		static bool IsMouseButtonPressedImpl(MouseButtonType button);
		static sf::Vector2f GetMousePositionImpl();

	private:
		static sf::WindowBase* s_TargetWindow;
	};

} // namespace fz


