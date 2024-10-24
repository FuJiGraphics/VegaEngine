#include "stdafx.h"
#include "Forest3.h"

void Forest3::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 980.0f, 3150.0f };
	Object.Size = { 370, 570 };
}

void Forest3::OnEvent(fz::Event& event)
{
}

void Forest3::OnUpdate(float dt)
{
}

void Forest3::OnDraw(Camera& camera)
{
}

void Forest3::OnCollide(const HitData& data)
{
	if (Utils::GetRandom(1, 8000) == 1)
	{
		SceneManager::ChangeScene("Battle");
		auto scene = SceneManager::GetCurrentScene();
		scene->InsertObject(data.GetLayer());
	}
}
