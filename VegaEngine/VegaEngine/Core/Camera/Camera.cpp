#include "Core/stdafx.h"
#include "Camera.h"

fz::Camera::Camera()
	: m_View()
	, m_Name("")
{
	// Empty
}

fz::Camera::~Camera()
{
}

void fz::Camera::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
	RenderTarget::setView(m_View);
	RenderTarget::draw(drawable, states);
}

void fz::Camera::SetCenter(const sf::Vector2f& pos)
{
	m_View.setCenter(pos);
}

void fz::Camera::SetRotate(float rotate)
{
	m_View.rotate(rotate);
}

void fz::Camera::SetZoom(float factor)
{
	m_View.zoom(factor);
}

void fz::Camera::Move(const sf::Vector2f& preset)
{
	m_View.move(preset);
}
