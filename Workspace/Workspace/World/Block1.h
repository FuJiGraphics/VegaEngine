#pragma once
#include "Engine.h"

class Block1 : public Layer
{
public:
	std::string GetClassName() const override { return "Block1"; }

	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	void OnUpdate(float dt) override;
	void OnDraw(Camera& camera) override;
};