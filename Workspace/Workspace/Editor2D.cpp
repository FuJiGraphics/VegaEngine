#include "Editor2D.h"

using namespace fz;

Editor2D::Editor2D(const std::string& name)
	: Layer(name)
	, camera("camera", { 1024, 768 })
{
}

void Editor2D::OnAttach()
{
	FramebufferSpec frameSpec;
	frameSpec.Width = 1024;
	frameSpec.Height = 768;
	frameSpec.MultisampleLevel = 1;
	frameBuffer = Framebuffer::Create(frameSpec);
}

void Editor2D::OnDetach()
{
}

void Editor2D::OnUpdate(float dt)
{
	camera.OnUpdate(dt);

	if (InputManager::IsKeyPressed(KeyType::Space))
	{
		static bool dockEnabled = true;
		dockEnabled = (dockEnabled) ? false : true;
		ImGuiManager::SetDocking(dockEnabled);
	}

	static sf::RectangleShape shape;
	shape.setSize({ 100.f, 100.f });
	shape.setPosition({ 1024.f * 0.5f, 768.f * 0.5f });
	Renderer2D::BeginScene(&camera, frameBuffer.get());
	Renderer2D::Draw(shape);
	Renderer2D::EndScene();
}

void Editor2D::OnEvent(fz::Event& ev)
{
	camera.OnEvent(ev);

}
