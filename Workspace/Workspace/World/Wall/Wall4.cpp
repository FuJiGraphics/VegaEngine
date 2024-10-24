#include "stdafx.h"
#include "Wall4.h"

void Wall4::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 200.0f, 2782.0f };
	Object.Size = { 84, 73 };
}

void Wall4::OnEvent(fz::Event& event)
{
}

void Wall4::OnUpdate(float dt)
{
}

void Wall4::OnDraw(Camera& camera)
{
}

void Wall4::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
