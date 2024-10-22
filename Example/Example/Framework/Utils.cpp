#include "stdafx.h"
#include "Utils.h"

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins preset)
{
	float x = 0;
	float y = 0;
	if (preset != Origins::Custom)
	{
		const auto& rect = obj.getLocalBounds();
		x = rect.width * ((int)preset % 3) * 0.5f;
		y = rect.height * ((int)preset / 3) * 0.5f;
		obj.setOrigin(x, y);
	}
	return { x, y };
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins preset)
{
	float x = 0;
	float y = 0;
	if (preset != Origins::Custom)
	{
		const auto& rect = obj.getLocalBounds();
		x = rect.width * ((int)preset % 3) * 0.5f;
		y = rect.height * ((int)preset / 3) * 0.5f;
		obj.setOrigin(x, y);
	}
	return { x, y };
}

