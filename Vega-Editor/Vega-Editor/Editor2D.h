#pragma once
#include <VegaEngine2.h>

class Editor2D : public fz::Layer
{
public:
	Editor2D(const std::string& name);

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnEvent(fz::Event& ev) override;
	void OnUI() override;

private:
	fz::CameraController camera;
	fz::Shared<fz::Framebuffer>	frameBuffer;
	unsigned int texId;
};