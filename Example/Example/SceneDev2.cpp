#include "stdafx.h"
#include "SceneDev2.h"
#include "Framework/SpriteGo.h"

SceneDev2::SceneDev2()
	: Scene(SceneIDs::Dev2)
{
	// Empty
}

void SceneDev2::Init()
{
	TextGo* text = new TextGo("Text", "res/fonts/KOMIKAP_.ttf");
	std::cout << "SceneDev1::Init()" << std::endl;
	fz::Texture::Load("res/graphics/player.png");
	AddGo(new SpriteGo("Player", "res/graphics/player.png"));
	AddGo(text);
	text->SetString("SceneDev2");
	text->SetOrigin(Origins::TopLeft);
	Scene::Init();
}

void SceneDev2::Release()
{
	std::cout << "SceneDev2::Release()" << std::endl;
	fz::Texture::Unload("res/Graphics/Player.png");
	Scene::Release();
}

void SceneDev2::Enter()
{
	std::cout << "SceneDev2::Enter()" << std::endl;
	fz::Texture::Load("res/Graphics/Player.png");

	Scene::Enter();
}

void SceneDev2::Exit()
{
	std::cout << "SceneDev2::Exit()" << std::endl;
	fz::Texture::Unload("res/Graphics/Player.png");
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().ChangeScene(SceneIDs::Dev1);
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
