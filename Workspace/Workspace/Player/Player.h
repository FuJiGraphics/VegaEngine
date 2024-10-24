#pragma once
#include "Engine.h"

class Player : public fz::GameObject
{
public:
	Player();

	std::string GetClassName() const override { return "Player"; }

	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	void OnUpdate(float dt) override;
	void OnDraw(Camera& camera) override;
	void OnCollide(const HitData& hit) override;
	void UpdateCansle();
	
// World
public:
	void SceneWorldInit();
	void SceneWorld(float dt);

// Battle
public:
	void SceneBattleInit();
	void SceneBattle(float dt);
	

private:
	AnimList animation;
	sf::Texture Tex;
	float Speed;
	sf::Vector2f PrevPos;
};
