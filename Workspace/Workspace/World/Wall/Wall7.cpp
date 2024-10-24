#include "stdafx.h"
#include "Wall7.h"

void Wall7::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 200.0f, 3927.0f };
	Object.Size = { 184, 73 };
}

void Wall7::OnEvent(fz::Event& event)
{
}

void Wall7::OnUpdate(float dt)
{
}

void Wall7::OnDraw(Camera& camera)
{
}

void Wall7::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
