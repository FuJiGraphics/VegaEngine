#include "Core/stdafx.h"
#include "Collider.h"

namespace fz {

	Collider::Collider()
		: m_isActivate(false)
		, m_IsDisplay(false)
		, m_className("")
		, m_ownerLayer(nullptr)
		, m_rect({0, 0, 0, 0})
	{
	}

	Collider::~Collider()
	{
		// Empty
	}

	void Collider::Set(const sf::Vector2f& origin, const sf::FloatRect& rect, const sf::Vector2f& scale)
	{
		m_Box.setOrigin(origin);
		m_Box.setPosition({ rect.left, rect.top });
		m_Box.setSize({ rect.width, rect.height });
		m_Box.setScale(scale);
		m_Box.setFillColor(sf::Color::Transparent);
		m_Box.setOutlineColor(sf::Color::White);
		m_Box.setOutlineThickness(3.0f);
		auto& globalPos = m_Box.getGlobalBounds();
		m_rect.x = globalPos.left;
		m_rect.y = globalPos.top;
		m_rect.w = m_rect.x + globalPos.width;
		m_rect.h = m_rect.y + globalPos.height;
	}

	const Rect& Collider::Get() const
	{
		return (m_rect);
	}

	void Collider::Activate(bool flags, const std::string& className, Layer* layer)
	{
		m_isActivate = flags;
		m_className = className;
		m_ownerLayer = layer;
	}

	void Collider::SetDisplay(bool enabled)
	{
		m_IsDisplay = enabled;
	}

	void Collider::SetOutlineColor(const sf::Color& color)
	{
		m_Box.setOutlineColor(color);
	}

	bool Collider::IsDisplay() const
	{
		return (m_IsDisplay);
	}

	sf::RectangleShape& Collider::GetBox()
	{
		return (m_Box);
	}

	bool Collider::IsActivated()
	{
		return (m_isActivate);
	}

	bool Collider::IsCollided(Collider& other)
	{
		if (this == &other || m_className == other.m_className)
			return (false);

		const Rect& srcRec = other.Get();
		if (m_rect.w < srcRec.x || m_rect.x > srcRec.w)
			return (false);
		if (m_rect.h < srcRec.y || m_rect.y > srcRec.h)
			return (false);

		if (m_ownerLayer)
			m_ownerLayer->OnCollide(other.m_ownerLayer, other.m_ownerLayer->GetName());

		other.SetOutlineColor(sf::Color::Red);
		this->SetOutlineColor(sf::Color::Red);
		return (true);
	}

	Layer* Collider::GetOwner()
	{
		return (m_ownerLayer);
	}

} // namespace fz