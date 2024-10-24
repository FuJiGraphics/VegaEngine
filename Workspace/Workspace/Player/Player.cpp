#include "stdafx.h"
#include "Player.h"

void Player::OnAttach()
{
	if (Texture::Load("res/player.png") == false)
	{
		std::cout << "failed to load image! >> " << std::endl;
		IsActivate = false;
		return;
	}
	Speed = 350.0f;
	Tex = Texture::Get("res/player.png");
	Object.Position = { 500.0f, 500.0f };
	Object.Scale = { 2.1f, 3.0f };
	Object.Sprite.setTexture(Tex);
	Object.Sprite.setTextureRect({ 0, 0, 60, 60 });
}

void Player::OnEvent(fz::Event& event)
{

}

void Player::OnUpdate(float dt)
{
	static float stride = 1920 / 1028.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Object.Position.x -= Speed * dt;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Object.Position.x += Speed * dt;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Object.Position.y -= Speed * dt * stride;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Object.Position.y += Speed * dt * stride;
	}
}

void Player::OnDraw(Camera& camera)
{
	camera.SetTarget(this);
	camera.draw(this);
}
