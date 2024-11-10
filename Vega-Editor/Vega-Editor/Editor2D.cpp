#include "Editor2D.h"

using namespace fz;

Editor2D::Editor2D(const std::string& name)
	: Layer(name)
	, camera(sf::Vector2f(1024.f, 768.f), false)
	, texId(0)
	, m_SquareEntity()
	, m_CameraEntity()
{

}

void Editor2D::OnAttach()
{
	FramebufferSpec frameSpec;
	frameSpec.Width = 1024;
	frameSpec.Height = 768;
	frameSpec.MultisampleLevel = 1;
	frameBuffer = Framebuffer::Create(frameSpec);
	texId = frameBuffer->GetBuffer().getTexture().getNativeHandle();

	m_ActiveScene = CreateShared<Scene>();

	// Entity
	m_SquareEntity = m_ActiveScene->CreateEntity("Square");
	auto& rect = m_SquareEntity.AddComponent<RectangleComponent>();
	rect.Rectangle.setPosition(1024.f * 0.5f, 768.f * 0.5f);
	rect.Rectangle.setSize({ 50.f, 50.f });
	Utils::SetOrigin(rect, Origins::MC);

	m_CameraEntity = m_ActiveScene->CreateEntity("Camera");

}

void Editor2D::OnDetach()
{
	texId = 0;
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

	Renderer2D::BeginScene(&camera, frameBuffer.get());
	Renderer2D::Draw(m_SquareEntity.GetComponent<RectangleComponent>());
	Renderer2D::EndScene();
}

void Editor2D::OnEvent(fz::Event& ev)
{
	camera.OnEvent(ev);
}

void Editor2D::OnUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport");
	ImVec2 vpSize = ImGui::GetContentRegionAvail();
	if (ImGui::IsWindowFocused())
		camera.SetActivated(true);
	else
		camera.SetActivated(false);

	auto& renderTex = frameBuffer->GetBuffer();
	ImGui::Image(renderTex);
	if (renderTex.getSize().x != vpSize.x || renderTex.getSize().y != vpSize.y)
	{
		renderTex.create(vpSize.x, vpSize.y);
		camera.SetSize(vpSize.x, vpSize.y);
	}
	ImGuiManager::ShowDemo();
	ImGui::End(); 
	ImGui::PopStyleVar();
}
