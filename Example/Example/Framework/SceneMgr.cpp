#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneDev2.h"

void SceneMgr::Init()
{
	scenes.push_back(new SceneDev1());
	scenes.push_back(new SceneDev2());

	for (auto scene : scenes)
	{
		scene->Init();
	}
	
	currScene = startScene;
	scenes[(int)currScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIDs id)
{
	scenes[(int)currScene]->Exit();
	currScene = id;
	scenes[(int)currScene]->Enter();

}

void SceneMgr::Updata(float dt)
{
	scenes[(int)currScene]->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currScene]->Draw(window);
}
