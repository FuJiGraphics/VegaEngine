#pragma once
#include "Engine.h"

class BattleZone : public Layer
{
public:
	std::string GetClassName() const override { return "BattleSpace"; }

	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	void OnUpdate(float dt) override;
	void OnDraw(Camera& camera) override;

private:
	sf::Texture Texture;
	Camera* camera;
};

