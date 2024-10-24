#include "stdafx.h"
#include "BattleZone.h"

void BattleZone::OnAttach()
{
	IsActivate = true;
	if (Texture::Load("res/Battle_Background.png") == false)
	{
		std::cout << "failed to load image! >> " << std::endl;
		IsActivate = false;
		return;
	}
	Texture = Texture::Get("res/Battle_Background.png");
	Object.Sprite.setTextureRect({ 0, 0, 256, 153 });
	Object.Position = { -450.0f, -140.0f };
	Object.Scale = { 10.2f, 8.2f };
	Object.Sprite.setTexture(Texture);
}

void BattleZone::OnEvent(fz::Event& event)
{
}

void BattleZone::OnUpdate(float dt)
{
	camera->SetCenter({ 500.f, 500.f });
}

void BattleZone::OnDraw(Camera& camera)
{
	camera.SetBlockArea(0.0f, 0.0f, 1280.0f, 8000.f);
	this->camera = &camera;
	camera.draw(this);
}
