#include "stdafx.h"
#include "Block8.h"

void Block8::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 780.0f, 1850.0f };
	Object.Size = { 390, 140 };
}

void Block8::OnEvent(fz::Event& event)
{
}

void Block8::OnUpdate(float dt)
{
}

void Block8::OnDraw(Camera& camera)
{
}

void Block8::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
