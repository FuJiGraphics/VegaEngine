#include "stdafx.h"
#include "Wall1.h"

void Wall1::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 201.0f, 780.0f };
	Object.Size = { 479, 650 };
}

void Wall1::OnEvent(fz::Event& event)
{
}

void Wall1::OnUpdate(float dt)
{
}

void Wall1::OnDraw(Camera& camera)
{
}

void Wall1::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
