#include "pch.h"
#include "InputManager.h"

namespace fz {

	bool InputManager::IsKeyPressedImpl(KeyType keycode)
	{
		return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keycode);
	}

	bool InputManager::IsMouseButtonPressedImpl(Button button)
	{
		return sf::Mouse::isButtonPressed((sf::Mouse::Button)button);
	}

	fz::Vec2f InputManager::GetMousePositionImpl()
	{
		const auto& mousePos = sf::Mouse::getPosition();
		float x = static_cast<float>(mousePos.x);
		float y = static_cast<float>(mousePos.y);
		return fz::Vec2f({ x, y });
	}

} // namespace fz