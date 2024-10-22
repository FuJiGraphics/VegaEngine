#pragma once
#include "Framework/Scene.h"

class SceneDev1 : public Scene
{
public:
	SceneDev1();
	~SceneDev1() = default;

public:
	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
