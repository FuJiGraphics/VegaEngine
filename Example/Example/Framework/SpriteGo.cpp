#include "stdafx.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& name, const std::string& textureID)
	: GameObject(name)
	, TexID(textureID)
{
	// Empty
}


void SpriteGo::Init()
{
	Sprite.setTexture(fz::Texture::Get(TexID));
	Sprite.setOrigin(Origin);
	Sprite.setPosition(Position);
}

void SpriteGo::Release()
{
}

void SpriteGo::Reset()
{
	Sprite.setTexture(fz::Texture::Get(TexID));
	Sprite.setOrigin(Origin);
}

void SpriteGo::SetPosition(const sf::Vector2f& pos)
{

}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	window.draw(Sprite);
}

void SpriteGo::SetOrigin(Origins preset)
{
	OriginPreset = preset;
	Origin = Utils::SetOrigin(Sprite, OriginPreset);
}

void SpriteGo::SetOrigin(const sf::Vector2f& origin)
{
	OriginPreset = Origins::Custom;
	Origin = origin;
	Sprite.setOrigin(Origin);
}