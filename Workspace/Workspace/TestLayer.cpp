#include "TestLayer.h"

using namespace fz;

TestLayer::TestLayer(const std::string& name)
	: Layer(name)
	, camera("camera", { 1024, 768 })
{
}

void TestLayer::OnAttach()
{

}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate(float dt)
{
	camera.OnUpdate(dt);

	static sf::RectangleShape shape;
	shape.setSize({ 100.f, 100.f });
	shape.setPosition({ 1024.f * 0.5f, 768.f * 0.5f });
	Renderer2D::BeginScene(&camera);
	Renderer2D::Draw(shape);
	Renderer2D::EndScene();
}

void TestLayer::OnEvent(fz::Event& ev)
{
	camera.OnEvent(ev);

}

void TestLayer::OnUI()
{
	ImGui::Begin("Viewport");


	ImGui::End();
}
