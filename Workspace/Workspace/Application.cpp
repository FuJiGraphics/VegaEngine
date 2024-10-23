#include "stdafx.h"
#include "Application.h"

using namespace fz;

void Application::OnAttach()
{
	Texture::Load("res/Graphics/Background.png");
	sf::Texture& tex = Texture::Get("res/Graphics/Background.png");
	sprite.setTexture(tex);
	speed = 1000.0f;
	m_Camera = nullptr;
}

void Application::OnEvent(fz::Event& event)
{
	auto& ev = event.get();
	switch (ev.type)
	{
		case sf::Event::KeyPressed:
		{
		}

	}
}

void Application::OnUpdate(float dt)
{
	if (m_Camera == nullptr)
		return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_Camera->Move({ speed * -1.0f * dt, 0.0f });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_Camera->Move({ speed * dt, 0.0f });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_Camera->Move({ 0.0f, speed * -1.0f * dt });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_Camera->Move({ 0.0f, speed * dt });
	}
}

void Application::OnDraw(Camera& camera)
{
	camera.draw(sprite);
	m_Camera = &camera;
}
