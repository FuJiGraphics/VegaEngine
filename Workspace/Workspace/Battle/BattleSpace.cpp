#include "stdafx.h"
#include "BattleSpace.h"

void BattleSpace::OnAttach()
{
	IsActivate = true;
	Speed = 300.f;
	Texture = Texture::Get("res/Battle_Background.png");
	Object.Sprite.setTextureRect({ 780, 60, 256, 35 });
	Object.Scale = { 3.5f, 10.0f };
	Object.Position = { -550.0f, 700.0f };
	Object.Sprite.setTexture(Texture);
}

void BattleSpace::OnEvent(fz::Event& event)
{
}

void BattleSpace::OnUpdate(float dt)
{
	if (Object.Position.x < -150.f)
		Object.Position.x += Speed * dt;
}

void BattleSpace::OnDraw(Camera& camera)
{
	camera.draw(this);
}
