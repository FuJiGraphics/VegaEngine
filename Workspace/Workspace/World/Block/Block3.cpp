#include "stdafx.h"
#include "Block3.h"


void Block3::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 1570.0f, 0.0f };
	Object.Size = { 100, 4000 };
}

void Block3::OnEvent(fz::Event& event)
{
}

void Block3::OnUpdate(float dt)
{
}

void Block3::OnDraw(Camera& camera)
{
}

void Block3::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
