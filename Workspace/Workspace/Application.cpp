#include "stdafx.h"
#include "Application.h"

using namespace fz;

void Application::OnAttach()
{
	Texture::Load("res/Graphics/Background.png");
	sf::Texture& tex = Texture::Get("res/Graphics/Background.png");
	sprite.setTexture(tex);
	view.setSize(200.0f, 200.0f);
}

void Application::OnEvent(fz::Event& event)
{
	auto& ev = event.get();
	switch (ev.type)
	{
		
	}
}

void Application::OnUpdate(float dt)
{
	
}

void Application::OnDraw(sf::RenderTexture& device)
{
	device.setView(view);
	device.draw(sprite);
}
