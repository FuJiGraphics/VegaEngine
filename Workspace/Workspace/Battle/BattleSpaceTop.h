#pragma once
#include "Engine.h"

class BattleSpaceTop : public Layer
{
public:
	std::string GetClassName() const override { return "BattleSpaceTop"; }

	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	void OnUpdate(float dt) override;
	void OnDraw(Camera& camera) override;

private:
	sf::Texture Texture;
	float Speed;
	Camera* camera;
};

