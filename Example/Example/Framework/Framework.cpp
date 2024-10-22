#include "stdafx.h"
#include "Framework.h"
#include "InputMgr.h"

#include "SpriteGo.h"
#include "Scene.h"

void Framework::Init(int width, int height, const std::string& name)
{
	window.create(sf::VideoMode(width, height), name);

	SceneMgr::Instance().Init();
}

void Framework::Do()
{
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		realDeltaTime = dt.asSeconds();
		deltaTime *= timeScale;
		realTime += realDeltaTime;
		time += deltaTime;

		// 이벤트 루프
		InputMgr::Clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			InputMgr::UpdateEvent(event); 
		}

		// 업데이트
		SceneMgr::Instance().Updata(dt.asSeconds());

		// 그리기
		window.clear();
		SceneMgr::Instance().Draw(window);
		window.display();
	}
}

void Framework::Release()
{
}
