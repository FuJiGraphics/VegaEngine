#include "stdafx.h"
#include "Wall5.h"

void Wall5::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 388.0f, 2782.0f };
	Object.Size = { 292, 73 };
}

void Wall5::OnEvent(fz::Event& event)
{
}

void Wall5::OnUpdate(float dt)
{
}

void Wall5::OnDraw(Camera& camera)
{
}

void Wall5::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
