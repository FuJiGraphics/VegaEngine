#include "stdafx.h"
#include "Player.h"
#include "Core/Camera/Camera.h"

Player::Player()
	: animation("Player")
{
}

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
	Object.Size = { 60, 60 };
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	CollideBox.Position = { 0.0f, +30.0f };
	IsDisplayCollider = true;

	animation.Insert("WalkDown", Object.Sprite);
	animation["WalkDown"].AddFrame({ sf::IntRect(0, 0, 60, 60), 0.3 });
	animation["WalkDown"].AddFrame({ sf::IntRect(63, 0, 60, 60), 0.3 });
	animation["WalkDown"].AddFrame({ sf::IntRect(128, 0, 60, 60), 0.3 });
	animation["WalkDown"].AddFrame({ sf::IntRect(193, 0, 60, 60), 0.3 });
	animation.Insert("WalkLeft", Object.Sprite);
	animation["WalkLeft"].AddFrame({ sf::IntRect(0, 63, 60, 60), 0.3 });
	animation["WalkLeft"].AddFrame({ sf::IntRect(63, 63, 60, 60), 0.3 });
	animation["WalkLeft"].AddFrame({ sf::IntRect(128, 63, 60, 60), 0.3 });
	animation["WalkLeft"].AddFrame({ sf::IntRect(193, 63, 60, 60), 0.3 });
	animation.Insert("WalkRight", Object.Sprite);
	animation["WalkRight"].AddFrame({ sf::IntRect(0, 126, 60, 60), 0.3 });
	animation["WalkRight"].AddFrame({ sf::IntRect(63, 126, 60, 60), 0.3 });
	animation["WalkRight"].AddFrame({ sf::IntRect(128, 126, 60, 60), 0.3 });
	animation["WalkRight"].AddFrame({ sf::IntRect(193, 126, 60, 60), 0.3 });
	animation.Insert("WalkUp", Object.Sprite);
	animation["WalkUp"].AddFrame({ sf::IntRect(0, 189, 60, 60), 0.3 });
	animation["WalkUp"].AddFrame({ sf::IntRect(63, 189, 60, 60), 0.3 });
	animation["WalkUp"].AddFrame({ sf::IntRect(128, 189, 60, 60), 0.3 });
	animation["WalkUp"].AddFrame({ sf::IntRect(193, 189, 60, 60), 0.3 });
}

void Player::OnEvent(fz::Event& event)
{
	
}

void Player::OnUpdate(float dt)
{
	animation.Update(dt);
	static float stride = 1920 / 1028.0f;
	std::string moveType;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Object.Position.x -= Speed * dt;
		animation.SetActivatedAll(false);
		animation["WalkLeft"].Activated = true;
		moveType = "WalkLeft";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Object.Position.x += Speed * dt;
		animation.SetActivatedAll(false);
		animation["WalkRight"].Activated = true;
		moveType = "WalkRight";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Object.Position.y -= Speed * dt * stride;
		animation.SetActivatedAll(false);
		animation["WalkUp"].Activated = true;
		moveType = "WalkUp";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Object.Position.y += Speed * dt * stride;
		animation.SetActivatedAll(false);

		animation["WalkDown"].Activated = true;
		moveType = "WalkDown";
	}
	else
		animation.SetActivatedAll(false);
}

void Player::OnDraw(Camera& camera)
{
	camera.draw(animation);
	camera.draw(this);
	camera.SetTarget(this);
}

void Player::OnCollide(const HitData& hit)
{
	std::cout << "플레이어 충돌!" << std::endl;
}
