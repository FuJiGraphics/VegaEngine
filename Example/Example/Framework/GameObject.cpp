#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(const std::string& name)
	: Name(name)
	, Active(true)
	, Position(0.0f, 0.0f)
{
	// Empty
}

void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Reset()
{
}

void GameObject::Update(float dt)
{
}

void GameObject::Draw(sf::RenderWindow& window)
{
}

void GameObject::SetOrigin(Origins preset)
{
	OriginPreset = preset;
	Origin = { 0.f, 0.f };
}

void GameObject::SetOrigin(const sf::Vector2f& origin)
{
	OriginPreset = Origins::Custom;
	Origin = origin;
}
