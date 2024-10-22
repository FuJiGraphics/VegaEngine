#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& name, const std::string& fontID)
	: GameObject(name)
	, Text()
	, FontID(fontID)
{
	// Empty
}

void TextGo::Init()
{
	fz::Font::Load(FontID);
	Text.setFont(fz::Font::Get(FontID));
	Text.setOrigin(Origin);
}

void TextGo::Release()
{
}

void TextGo::Reset()
{
	fz::Font::Load(FontID);
	Text.setFont(fz::Font::Get(FontID));
	Text.setOrigin(Origin);
}

void TextGo::SetPosition(const sf::Vector2f& pos)
{
	Position = pos;
	Text.setPosition(pos);
}

void TextGo::Draw(sf::RenderWindow& window)
{
	window.draw(Text);
}

void TextGo::SetString(const std::string& text)
{
	Text.setString(text);
}

void TextGo::SetOrigin(Origins preset)
{
	OriginPreset = preset;
	Origin = Utils::SetOrigin(Text, OriginPreset);
}

void TextGo::SetOrigin(const sf::Vector2f& origin)
{
	OriginPreset = Origins::Custom;
	Origin = origin;
	Text.setOrigin(origin);
}
