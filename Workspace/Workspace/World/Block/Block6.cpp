#include "stdafx.h"
#include "Block6.h"

void Block6::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 200.0f, 3300.0f };
	Object.Size = { 750, 120 };
}

void Block6::OnEvent(fz::Event& event)
{
}

void Block6::OnUpdate(float dt)
{
}

void Block6::OnDraw(Camera& camera)
{
}

void Block6::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
