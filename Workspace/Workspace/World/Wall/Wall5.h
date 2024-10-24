#pragma once
#include "Engine.h"

class Wall5 : public Layer
{
public:
	std::string GetClassName() const override { return "Wall5"; }

	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	void OnUpdate(float dt) override;
	void OnDraw(Camera& camera) override;
	void OnCollide(const HitData& data) override;
};

