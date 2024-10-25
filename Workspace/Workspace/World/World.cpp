#include "stdafx.h"
#include "World.h"

void World::OnAttach()
{
	float aspect = 1280.f / 768.f;
	Texture::Load("res/Map.png");
	Texture = Texture::Get("res/Map.png");
	Object.Position = { 0.0f, 0.0f };
	Object.Scale = { 3.68f * aspect, 5.36f * aspect };
	Object.Sprite.setTexture(Texture);
	camera = nullptr;
	Sound::Load("res/sound.mp3");
	WorldSound.setBuffer(Sound::Get("res/sound.mp3"));
	this->PlayWorldSound();
}

void World::OnEvent(fz::Event& event)
{
}

void World::OnUpdate(float dt)
{
}

void World::OnDraw(Camera& camera)
{
	camera.SetBlockArea(0.0f, 0.0f, 1280.f * 1.37f, 4000.f);
	camera.draw(this);
}

void World::PlayWorldSound()
{
	WorldSound.play();
}

