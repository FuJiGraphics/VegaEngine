#include "stdafx.h"
#include "Engine.h"
#include "Application.h"

WindowInfo CreateApplication()
{
	return { 1280, 768, "Pokemon" };
}

void Runtime(System& system)
{
	fz::SceneManager::InsertScene("1");
	auto scene = fz::SceneManager::GetCurrentScene();
	scene->InsertOverlay<Application>(new Application);
}

int main(void)
{
	BeginProcess();
	return (0);
}