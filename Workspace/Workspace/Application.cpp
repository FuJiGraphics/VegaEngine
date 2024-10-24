#include "stdafx.h"
#include "Application.h"
#include "World/World.h"
#include "World/Block1.h"
#include "Player/Player.h"

using namespace fz;

void Application::OnAttach()
{
	Scene* scene = SceneManager::GetCurrentScene();
	scene->InsertOverlay<World>(new World);
	scene->InsertObject<Player>(new Player());

	// Àå¾Ö¹°
	scene->InsertOverlay(new Block1);
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

