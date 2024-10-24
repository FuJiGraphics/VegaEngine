#include "stdafx.h"
#include "Application.h"

using namespace fz;

void Application::OnAttach()
{
	Scene* scene = SceneManager::GetCurrentScene();
	Player* player = new Player();
	scene->InsertOverlay<World>(new World);
	scene->InsertObject<Player>(new Player());

	// Àå¾Ö¹°
	scene->InsertOverlay(new Block1);
	scene->InsertOverlay(new Block2);
	scene->InsertOverlay(new Block3);
	scene->InsertOverlay(new Block4);
	scene->InsertOverlay(new Block5);
	scene->InsertOverlay(new Block6);
	scene->InsertOverlay(new Block7);
	scene->InsertOverlay(new Block8);
	scene->InsertObject(new Wall1);
	scene->InsertObject(new Wall2);
	scene->InsertObject(new Wall3);
	scene->InsertObject(new Wall4);
	scene->InsertObject(new Wall5);
	scene->InsertObject(new Wall6);
	scene->InsertObject(new Wall7);
	scene->InsertObject(new Wall8);
	scene->InsertObject(new Wall9);
	scene->InsertOverlay(new Forest1);
	scene->InsertOverlay(new Forest2);
	scene->InsertOverlay(new Forest3);
	scene->InsertOverlay(new Sigh1);

	Scene* battleScene = SceneManager::GetScene("Battle");
	if (battleScene != nullptr)
	{
		battleScene->InsertOverlay(new BattleZone);
		battleScene->InsertOverlay(new BattleSpace);
		battleScene->InsertOverlay(new BattleSpaceTop);
	}
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

