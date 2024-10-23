#pragma once
#include "Engine.h"

class World : public Layer
{
public:
	std::string GetClassName() const override { return "World"; }

	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	void OnUpdate(float dt) override;
	void OnDraw(Camera& camera) override;

private:
	sf::Texture Body;
	Camera* camera;
};

