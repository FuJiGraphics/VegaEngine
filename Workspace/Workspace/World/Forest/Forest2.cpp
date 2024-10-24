#include "stdafx.h"
#include "Forest2.h"

void Forest2::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 1180.0f, 1700.0f };
	Object.Size = { 370, 600 };
}

void Forest2::OnEvent(fz::Event& event)
{
}

void Forest2::OnUpdate(float dt)
{
}

void Forest2::OnDraw(Camera& camera)
{
}

void Forest2::OnCollide(const HitData& data)
{
	if (Utils::GetRandom(1, 5000) == 1)
	{
		SceneManager::ChangeScene("Battle");
		auto scene = SceneManager::GetCurrentScene();
		scene->InsertObject(data.GetLayer());
	}
}
