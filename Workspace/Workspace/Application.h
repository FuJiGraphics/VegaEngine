#pragma once

// Headers
#include "Engine.h"

class Application : public fz::Layer
{
public:
	std::string GetClassName() const override { return "Application"; }
	
	void	OnAttach() override;
	void	OnEvent(fz::Event& event) override;
	void	OnUpdate(float dt) override;
	void	OnDraw(sf::RenderTexture& device) override;

private:
	sf::Sprite sprite;
};

