#include "stdafx.h"
#include "Wall2.h"

void Wall2::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 395.0f, 1920.0f };
	Object.Size = { 370, 80 };
}

void Wall2::OnEvent(fz::Event& event)
{
}

void Wall2::OnUpdate(float dt)
{
}

void Wall2::OnDraw(Camera& camera)
{
}

void Wall2::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
