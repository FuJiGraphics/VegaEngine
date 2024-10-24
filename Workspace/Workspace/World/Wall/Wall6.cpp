#include "stdafx.h"
#include "Wall6.h"

void Wall6::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 783.0f, 2782.0f };
	Object.Size = { 772, 73 };
}

void Wall6::OnEvent(fz::Event& event)
{
}

void Wall6::OnUpdate(float dt)
{
}

void Wall6::OnDraw(Camera& camera)
{
}

void Wall6::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
