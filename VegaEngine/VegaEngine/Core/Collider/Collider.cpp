#include "Core/stdafx.h"
#include "Collider.h"
#include "Core/Layer/Layer.h"

namespace fz {

	Collider::Collider()
		: m_rect({0, 0, 0, 0})
	{
		m_Box.setFillColor(sf::Color::Transparent);
		m_Box.setOutlineColor(sf::Color::White);
		m_Box.setOutlineThickness(3.0f);
	}

	Collider::~Collider()
	{
		// Empty
	}

	void Collider::SetPosition(const sf::FloatRect& rect)
	{
		m_Box.setPosition({ rect.left, rect.top });
		m_Box.setSize({ rect.width, rect.height });
		auto& globalPos = m_Box.getGlobalBounds();
		m_rect.x = static_cast<int>(globalPos.left);
		m_rect.y = static_cast<int>(globalPos.top);
		m_rect.w = m_rect.x + static_cast<int>(globalPos.width);
		m_rect.h = m_rect.y + static_cast<int>(globalPos.height);
	}

	void Collider::SetPosition(const Layer* layer)
	{
		auto& origin = layer->GetOrigin();
		auto& pos = layer->GetPosition();
		auto& scale = layer->GetScale();
		auto& size = layer->GetSize();
		sf::FloatRect tRec;
		auto colBoxPos = layer->GetCollidePos();
		tRec.left = pos.x + origin.x + colBoxPos.x;
		tRec.top = pos.x + origin.y + colBoxPos.y;
		auto colBoxSize = layer->GetCollideSize();
		tRec.width = colBoxSize.x ? (float)colBoxSize.x : (float)size.x;
		tRec.height = colBoxSize.y ? (float)colBoxSize.y : (float)size.y;
		m_Box.setOrigin(origin);
		m_Box.setPosition({ tRec.left, tRec.top });
		m_Box.setSize({ tRec.width, tRec.height });
		m_Box.setScale(scale);
		auto& globalPos = m_Box.getGlobalBounds();
		m_rect.x = static_cast<int>(globalPos.left);
		m_rect.y = static_cast<int>(globalPos.top);
		m_rect.w = m_rect.x + static_cast<int>(globalPos.width);
		m_rect.h = m_rect.y + static_cast<int>(globalPos.height);
	}

	bool Collider::IsCollided(Collider& other)
	{
		if (this == &other)
			return (false);
		const Rect& srcRec = other.GetRect();
		if (m_rect.x + m_rect.w < srcRec.x || m_rect.x > srcRec.x + srcRec.w)
			return (false);
		if (m_rect.y + m_rect.h < srcRec.y || m_rect.y > srcRec.y + srcRec.h)
			return (false);
		return (true);
	}

	bool Collider::IsCollided(const Collider& other) const
	{
		return this->IsCollided(other);
	}

} // namespace fz