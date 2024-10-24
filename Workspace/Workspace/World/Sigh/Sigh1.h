#pragma once
#include "Engine.h"

class Sigh1 : public Layer
{
public:
	std::string GetClassName() const override { return "Sigh1"; }

	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	void OnUpdate(float dt) override;
	void OnDraw(Camera& camera) override;
};
