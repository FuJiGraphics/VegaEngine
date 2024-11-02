#pragma once
#include <VegaEngine2.h>

class TestLayer : public fz::Layer
{
public:
	TestLayer(const std::string& name);

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnEvent(fz::Event& ev) override;
	void OnUI() override;

private:
	fz::CameraController camera;
};