#pragma once
#include "Framework/Scene.h"

class SceneDev2 : public Scene
{
public:
	SceneDev2();
	~SceneDev2() = default;

public:
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

