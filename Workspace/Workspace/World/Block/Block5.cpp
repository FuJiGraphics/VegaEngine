#include "stdafx.h"
#include "Block5.h"

void Block5::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 690.0f, 560.0f };
	Object.Size = { 80, 850 };
}

void Block5::OnEvent(fz::Event& event)
{
}

void Block5::OnUpdate(float dt)
{
}

void Block5::OnDraw(Camera& camera)
{
}

void Block5::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
