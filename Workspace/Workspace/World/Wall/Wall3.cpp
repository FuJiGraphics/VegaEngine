#include "stdafx.h"
#include "Wall3.h"

void Wall3::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 781.0f, 780.0f };
	Object.Size = { 390, 60 };
}

void Wall3::OnEvent(fz::Event& event)
{
}

void Wall3::OnUpdate(float dt)
{
}

void Wall3::OnDraw(Camera& camera)
{
}

void Wall3::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
