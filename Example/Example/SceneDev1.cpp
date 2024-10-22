#include "stdafx.h"
#include "SceneDev1.h"
#include "Framework/SpriteGo.h"

SceneDev1::SceneDev1()
	: Scene(SceneIDs::Dev1)
{
	// Empty
}

void SceneDev1::Init()
{
	std::cout << "SceneDev1::Init()" << std::endl;
	fz::Texture::Load("res/graphics/background.png");
	AddGo(new SpriteGo("Background", "res/graphics/background.png"));
	TextGo* text = AddGo(new TextGo("Text", "res/fonts/KOMIKAP_.ttf"));
	text->SetString("SceneDev1");
	text->SetOrigin(Origins::TopLeft);
	Scene::Init();
}

void SceneDev1::Release()
{
	std::cout << "SceneDev1::Release()" << std::endl;
	fz::Texture::Unload("res/graphics/background.png");

	Scene::Release();
}

void SceneDev1::Enter()
{
	std::cout << "SceneDev1::Enter()" << std::endl;
	fz::Texture::Load("res/graphics/background.png");
	Scene::Enter();
}

void SceneDev1::Exit()
{
	std::cout << "SceneDev1::Exit()" << std::endl;
	fz::Texture::Unload("res/graphics/background.png");
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().ChangeScene(SceneIDs::Dev2);
	}
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
