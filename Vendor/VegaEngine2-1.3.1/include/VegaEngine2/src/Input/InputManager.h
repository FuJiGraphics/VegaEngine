#pragma once

#include "Core/Core.h"

namespace fz {

	class InputManager
	{
	public:
		inline static bool IsKeyPressed(KeyType keycode) {
			return InputManager::IsKeyPressedImpl(keycode); 
		}
		inline static bool IsMouseButtonPressed(Button button) {
			return InputManager::IsMouseButtonPressedImpl(button);
		}
		inline static fz::Vec2f GetMousePosition() {
			return InputManager::GetMousePositionImpl();
		}

	protected:
		static bool IsKeyPressedImpl(KeyType keycode);
		static bool IsMouseButtonPressedImpl(Button button);
		static fz::Vec2f GetMousePositionImpl();
	};

} // namespace fz


