#include "stdafx.h"
#include "Application.h"
#include "World/World.h"
#include "Player/Player.h"

using namespace fz;

void Application::OnAttach()
{
	Scene* scene = SceneManager::GetCurrentScene();
	scene->InsertOverlay<World>(new World);
	scene->InsertOverlay<Player>(new Player);
}

void Application::OnEvent(fz::Event& event)
{
	auto& ev = event.get();
	switch (ev.type)
	{
		case sf::Event::KeyPressed:
		{
		}

	}
}

void Application::OnDraw(Camera& camera)
{
}

