#include "stdafx.h"
#include "BattleSpaceTop.h"

void BattleSpaceTop::OnAttach()
{
	IsActivate = true;
	Speed = 300.f;
	Texture = Texture::Get("res/Battle_Background.png");
	Object.Sprite.setTextureRect({ 780, 20, 256, 40 });
	Object.Scale = { 3.5f, 7.0f };
	Object.Position = { 700.0f, 300.0f };
	Object.Sprite.setTexture(Texture);
}

void BattleSpaceTop::OnEvent(fz::Event& event)
{
}

void BattleSpaceTop::OnUpdate(float dt)
{
	if (Object.Position.x > 300.f)
		Object.Position.x -= Speed * dt;
}

void BattleSpaceTop::OnDraw(Camera& camera)
{
	camera.draw(this);
}
