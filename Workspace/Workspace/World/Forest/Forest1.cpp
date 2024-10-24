#include "stdafx.h"
#include "Forest1.h"

void Forest1::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 780.0f, 850.0f };
	Object.Size = { 750, 600 };
}

void Forest1::OnEvent(fz::Event& event)
{
}

void Forest1::OnUpdate(float dt)
{
}

void Forest1::OnDraw(Camera& camera)
{
}

void Forest1::OnCollide(const HitData& data)
{
	if (Utils::GetRandom(1, 8000) == 1)
	{
		SceneManager::ChangeScene("Battle");
		auto scene = SceneManager::GetCurrentScene();
		scene->InsertObject(data.GetLayer());
	}
}
