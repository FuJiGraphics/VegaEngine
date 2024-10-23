#include "stdafx.h"
#include "World.h"

void World::OnAttach()
{
	Texture::Load("res/Map.png");
	Body = Texture::Get("res/Map.png");
	camera = nullptr;
}

void World::OnEvent(fz::Event& event)
{
	if (camera == nullptr)
		return;

	switch (event.get().type)
	{
	case sf::Event::KeyPressed:
	{
		switch (event.get().key.code)
		{
		case sf::Keyboard::Left:
			camera->Move({ -10.0f, 0.0f });
			break;
		case sf::Keyboard::Right:
			camera->Move({ 10.0f, 0.0f });
			break;
		case sf::Keyboard::Up:
			camera->Move({ 0.0f, +10.0f });
			break;
		case sf::Keyboard::Down:
			camera->Move({ 0.0f, 10.0f });
			break;
		}
	}

		break;
	}
}

void World::OnUpdate(float dt)
{
}

void World::OnDraw(Camera& camera)
{
	sf::Sprite a(Body);
	a.setScale(5.0f, 10.0f);
	camera.draw(a);
	this->camera = &camera;
}
