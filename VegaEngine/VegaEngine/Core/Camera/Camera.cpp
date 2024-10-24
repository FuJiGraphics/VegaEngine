#include "Core/stdafx.h"
#include <SFML/Graphics.hpp>
#include "Camera.h"

namespace fz {
	Camera::Camera()
		: m_View()
		, m_Name("")
		, m_Target(nullptr)
	{
		// Empty
	}

	Camera::~Camera()
	{
		// Empty
	}

	void Camera::draw(const sf::Drawable& obj, const sf::RenderStates& states)
	{
		RenderTexture::draw(obj, states);
	}

	void Camera::draw(Layer* object, const sf::RenderStates& states)
	{
		auto& obj = object->GetObject();
		auto& sprite = obj.Sprite;
		sprite.setOrigin(obj.Origin);
		sprite.setPosition(obj.Position);
		sprite.setScale(obj.Scale);
		if (m_Target == object)
		{
			auto prev = m_View.getCenter();
			auto next = obj.Position;
			auto viewSize = m_View.getSize();
			float hw = viewSize.x * 0.5f;
			float hh = viewSize.y * 0.5f;
			if (next.x - hw < m_BlockArea.getPosition().x || next.x + hw > m_BlockArea.width)
				next.x = prev.x;
			if (next.y - hh < m_BlockArea.getPosition().y || next.y + hh > m_BlockArea.height)
				next.y = prev.y;
			m_View.setCenter(next);
		}
		RenderTexture::setView(m_View);
		RenderTexture::draw(sprite);
	}

	void Camera::SetCenter(const sf::Vector2f& pos)
	{
		m_View.setCenter(pos);
	}

	void Camera::SetRotate(float rotate)
	{
		m_View.rotate(rotate);
	}

	void Camera::SetZoom(float factor)
	{
		m_View.zoom(factor);
	}

	void Camera::Move(const sf::Vector2f& preset)
	{
		m_View.move(preset);
	}

	void Camera::SetBlockArea(float x, float y, float width, float height)
	{
		m_BlockArea = { x, y, width, height };
	}

} // namespace fz