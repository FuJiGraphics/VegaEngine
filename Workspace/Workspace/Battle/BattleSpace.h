#pragma once
#include "Engine.h"

class BattleSpace : public Layer
{
public:
	std::string GetClassName() const override { return "BattleSpace"; }

	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	void OnUpdate(float dt) override;
	void OnDraw(Camera& camera) override;

private:
	sf::Texture Texture;
	float Speed;
	Camera* camera;
};

