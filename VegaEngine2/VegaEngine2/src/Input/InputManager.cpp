#include "pch.h"
#include "InputManager.h"

namespace fz {

	sf::WindowBase* InputManager::s_TargetWindow = nullptr;

	bool InputManager::IsKeyPressedImpl(KeyType keycode)
	{
		return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keycode);
	}

	bool InputManager::IsMouseButtonPressedImpl(Button button)
	{
		return sf::Mouse::isButtonPressed((sf::Mouse::Button)button);
	}

	sf::Vector2f InputManager::GetMousePositionImpl()
	{
		sf::Vector2i mousePos;
		// case 1 Target Window Mouse Position
		if (s_TargetWindow)
			mousePos = sf::Mouse::getPosition(*s_TargetWindow);
		// case 2 Global position in the desktop
		else
			mousePos = sf::Mouse::getPosition();
		float x = static_cast<float>(mousePos.x);
		float y = static_cast<float>(mousePos.y);
		return sf::Vector2f({ x, y });
	}

} // namespace fz