#pragma once

// Headers
#include "Engine.h"

class Application : public fz::Layer
{
public:
	std::string GetClassName() const override { return "Application"; }
	
	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	void OnDraw(Camera& camera) override;
};

