#include "Core/stdafx.h"
#include "Collider.h"

namespace fz {

	Collider::Collider()
		: m_isActivate(false)
		, m_isDisplay(false)
		, m_rect({0, 0, 0, 0})
	{
		m_Box.setFillColor(sf::Color::Transparent);
		m_Box.setOutlineColor(sf::Color::White);
		m_Box.setOutlineThickness(3.0f);
	}

	Collider::~Collider()
	{
		// Empty
	}

	void Collider::SetPosition(const sf::Vector2f& origin, const sf::FloatRect& rect, const sf::Vector2f& scale)
	{
		sf::FloatRect tRec;
		tRec.left = rect.left + origin.x;
		tRec.top = rect.top + origin.y;
		tRec.width = rect.width;
		tRec.height = rect.height;
		m_Box.setOrigin(origin);
		m_Box.setPosition({ tRec.left, tRec.top });
		m_Box.setSize({ tRec.width, tRec.height });
		m_Box.setScale(scale);
		auto& globalPos = m_Box.getGlobalBounds();
		m_rect.x = globalPos.left;
		m_rect.y = globalPos.top;
		m_rect.w = m_rect.x + globalPos.width;
		m_rect.h = m_rect.y + globalPos.height;
		m_isActivate = true;
	}

	void Collider::SetPosition(const Layer* layer)
	{
		auto& origin = layer->GetOrigin();
		auto& pos = layer->GetPosition();
		auto& scale = layer->GetScale();
		auto& size = layer->GetSize();
		this->SetPosition(origin, { pos.x, pos.y, size.x, size.y }, scale);
	}

	bool Collider::IsCollided(Collider& other)
	{
		if (this == &other)
			return (false);
		const Rect& srcRec = other.Get();
		if (m_rect.w < srcRec.x || m_rect.x > srcRec.w)
			return (false);
		if (m_rect.h < srcRec.y || m_rect.y > srcRec.h)
			return (false);
		return (true);
	}

} // namespace fz