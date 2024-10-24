#pragma once
#include "Engine.h"
class Forest1 : public Layer
{
public:
	std::string GetClassName() const override { return "Forest1"; }

	void OnAttach() override;
	void OnEvent(fz::Event& event) override;
	void OnUpdate(float dt) override;
	void OnDraw(Camera& camera) override;
	void OnCollide(const HitData& data) override;
};

