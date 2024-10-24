#include "stdafx.h"
#include "Block2.h"

void Block2::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 200.0f, 0.0f };
	Object.Size = { 570, 270 };
}

void Block2::OnEvent(fz::Event& event)
{
}

void Block2::OnUpdate(float dt)
{
}

void Block2::OnDraw(Camera& camera)
{
}

void Block2::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
