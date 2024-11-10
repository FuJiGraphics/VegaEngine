#include "pch.h"
#include "Camera.h"

namespace fz {

	OrthoCamera::OrthoCamera()
		: m_View()
	{
		// Empty
	}

	OrthoCamera::OrthoCamera(const OrthoCamera& other)
		: m_View(other.m_View)
	{
		// Empty
	}

	OrthoCamera::OrthoCamera(OrthoCamera&& other)
		: m_View(other.m_View)
	{
		other.m_View = sf::View();
	}

	OrthoCamera::OrthoCamera(const sf::FloatRect& viewport)
		: m_View(viewport)
	{
		// Empty
	}

	OrthoCamera::OrthoCamera(const sf::Vector2f& center, const sf::Vector2f& size)
		: m_View(center, size)
	{
		// Empty
	}

	OrthoCamera::OrthoCamera(const sf::View& view)
		: m_View(view)
	{
		// Empty
	}

	void OrthoCamera::SetCenter(float x, float y)
	{
		m_View.setCenter(x, y);
	}

	void OrthoCamera::SetCenter(const sf::Vector2f& center)
	{
		m_View.setCenter(center);
	}

	void OrthoCamera::SetSize(float width, float height)
	{
		m_View.setSize(width, height);
	}

	void OrthoCamera::SetSize(const sf::Vector2f& size)
	{
		m_View.setSize(size);
	}

	void OrthoCamera::SetRotation(float angle)
	{
		m_View.setRotation(angle);
	}

	void OrthoCamera::SetViewport(const sf::FloatRect& viewport)
	{
		m_View.setViewport(viewport);
	}

	void OrthoCamera::Reset(const sf::FloatRect& rectangle)
	{
		m_View.reset(rectangle);
	}

	const sf::Vector2f& OrthoCamera::GetCenter() const
	{
		return m_View.getCenter();
	}

	const sf::Vector2f& OrthoCamera::GetSize() const
	{
		return m_View.getSize();
	}

	float OrthoCamera::GetRotation() const
	{
		return m_View.getRotation();
	}

	const sf::FloatRect& OrthoCamera::GetViewport() const
	{
		return m_View.getViewport();
	}

	void OrthoCamera::Move(float offsetX, float offsetY)
	{
		m_View.move(offsetX, offsetY);
	}

	void OrthoCamera::Move(const sf::Vector2f& offset)
	{
		m_View.move(offset);
	}

	void OrthoCamera::Rotate(float angle)
	{
		m_View.rotate(angle);
	}

	void OrthoCamera::Zoom(float factor)
	{
		m_View.zoom(factor);
	}

	const sf::Transform& OrthoCamera::GetTransform() const
	{
		return m_View.getTransform();
	}

	const sf::Transform& OrthoCamera::GetInverseTransform() const
	{
		return m_View.getInverseTransform();
	}

	const sf::View& OrthoCamera::GetView() const
	{
		return m_View;
	}

	sf::View& OrthoCamera::GetView()
	{
		return m_View;
	}

} // namespace fz
