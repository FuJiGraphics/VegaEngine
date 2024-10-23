#include "stdafx.h"
#include "Engine.h"
#include "Application.h"

WindowInfo CreateApplication()
{
	return { 1920, 1080, "Game" };
}

void Runtime(System& system)
{
	auto sceneList = system.GetSceneList();
	auto scene = sceneList->GetCurrentScene();
	(*scene)->InsertOverlay<Application>(new Application);
}

int main(void)
{
	BeginProcess();
	return (0);
}