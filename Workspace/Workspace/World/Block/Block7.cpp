#include "stdafx.h"
#include "Block7.h"

void Block7::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 200.0f, 1850.0f };
	Object.Size = { 180, 140 };
}

void Block7::OnEvent(fz::Event& event)
{
}

void Block7::OnUpdate(float dt)
{
}

void Block7::OnDraw(Camera& camera)
{
}

void Block7::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
