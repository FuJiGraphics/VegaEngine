#include "stdafx.h"
#include "Block4.h"

void Block4::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 980.0f, 0.0f };
	Object.Size = { 570, 270 };
}

void Block4::OnEvent(fz::Event& event)
{
}

void Block4::OnUpdate(float dt)
{
}

void Block4::OnDraw(Camera& camera)
{
}

void Block4::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
