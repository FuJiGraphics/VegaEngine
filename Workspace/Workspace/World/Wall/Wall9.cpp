#include "stdafx.h"
#include "Wall9.h"

void Wall9::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 1370.0f, 3357.0f };
	Object.Size = { 192, 73 };
}

void Wall9::OnEvent(fz::Event& event)
{
}

void Wall9::OnUpdate(float dt)
{
}

void Wall9::OnDraw(Camera& camera)
{
}

void Wall9::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
