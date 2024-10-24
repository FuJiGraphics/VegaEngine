#include "stdafx.h"
#include "Sigh1.h"

void Sigh1::OnAttach()
{
	IsDisplayCollider = true;
	auto currScene = SceneManager::GetCurrentScene();
	currScene->InsertCollideSystem(this);
	Object.Position = { 680.0f, 3877.0f };
	Object.Size = { 94, 123 };
}

void Sigh1::OnEvent(fz::Event& event)
{
}

void Sigh1::OnUpdate(float dt)
{
}

void Sigh1::OnDraw(Camera& camera)
{
}