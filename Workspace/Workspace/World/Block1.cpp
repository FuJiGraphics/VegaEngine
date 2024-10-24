#include "stdafx.h"
#include "Block1.h"

void Block1::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 90.0f, 0.0f };
	Object.Size = { 100, 4000 };
}

void Block1::OnEvent(fz::Event& event)
{
}

void Block1::OnUpdate(float dt)
{
}

void Block1::OnDraw(Camera& camera)
{
}
