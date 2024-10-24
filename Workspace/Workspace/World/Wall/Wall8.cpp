#include "stdafx.h"
#include "Wall8.h"

void Wall8::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 782.0f, 3927.0f };
	Object.Size = { 770, 73 };
}

void Wall8::OnEvent(fz::Event& event)
{
}

void Wall8::OnUpdate(float dt)
{
}

void Wall8::OnDraw(Camera& camera)
{
}

void Wall8::OnCollide(const HitData& data)
{
	if (data.ClassName() == "Player")
	{
		Player* p = dynamic_cast<Player*>(data.GetLayer());
		p->UpdateCansle();
	}
}
