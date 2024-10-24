#pragma once
#include "Engine.h"

class Player : public fz::GameObject
{
public:
	std::string GetClassName() const override { return "Player"; }

	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	void OnUpdate(float dt) override;
	void OnDraw(Camera& camera) override;

private:
	sf::Texture Tex;
	float Speed;
};
