#pragma once
#include "Engine.h"

class Forest3 : public Layer
{
public:
	std::string GetClassName() const override { return "Forest3"; }

	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	void OnUpdate(float dt) override;
	void OnDraw(Camera& camera) override;
	void OnCollide(const HitData& data) override;
};