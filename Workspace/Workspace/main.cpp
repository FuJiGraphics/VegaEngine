#include "stdafx.h"
#include "Engine.h"
#include "Application.h"

WindowInfo CreateApplication()
{
	return { 1280, 768, "Pokemon" };
}

void Runtime(System& system)
{
	SceneManager::InsertScene("World");
	SceneManager::InsertScene("Battle");
	auto scene = SceneManager::GetCurrentScene();
	scene->InsertOverlay<Application>(new Application);
}

int main(void)
{
	BeginProcess();
	return (0);
}