#include "pch.h"
#include "Transform.h"

namespace fz {
	Transform::Transform()
		: m_Translate{ 0.0f, 0.0f }
		, m_Rotation{ 0.0f }
		, m_Scale{ 1.0f, 1.0f }
		, m_Origin{ 0.0f, 0.0f }
		, m_World{ sf::Transform::Identity }
	{
	}
	void Transform::SetTranslate(const sf::Vector2f& pos)
	{
		m_Translate = pos;
		ResetTransform();
	}

	void Transform::SetTranslate(float posX, float posY)
	{
		m_Translate = { posX, posY };
		ResetTransform();
	}

	void Transform::SetRotation(float angle)
	{
		m_Rotation = angle;
		ResetTransform();
	}

	void Transform::SetScale(const sf::Vector2f& factors)
	{
		m_Scale = factors;
		ResetTransform();
	}

	void Transform::SetScale(float factorX, float factorY)
	{
		m_Scale = { factorX, factorY };
		ResetTransform();
	}

	void Transform::SetOrigin(const sf::Vector2f& origin)
	{
		m_Origin = origin;
		ResetTransform();
	}

	void Transform::SetOrigin(float originX, float originY)
	{
		m_Origin = { originX, originY };
		m_Origin *= -1.0f;
		ResetTransform();
	}

	sf::Vector2f Transform::GetTranslate() const
	{
		return m_Translate;
	}

	float Transform::GetRotation() const
	{
		return m_Rotation;
	}

	sf::Vector2f Transform::GetScale() const
	{
		return m_Scale;
	}

	sf::Vector2f Transform::GetOrigin() const
	{
		return m_Origin;
	}

	sf::Transform& Transform::GetRawTransform()
	{
		return m_World;
	}

	const sf::Transform& Transform::GetRawTransform() const
	{
		return m_World;
	}

	sf::Vector2f Transform::operator*(const sf::Vector2f& other) const
	{
		return m_World * other;
	}

	Transform::operator sf::Transform& ()
	{
		return m_World;
	}

	Transform::operator const sf::Transform& () const
	{
		return m_World;
	}

	void Transform::ResetTransform()
	{
		m_World = sf::Transform::Identity;
		m_World.translate(m_Translate);
		m_World.rotate(m_Rotation);
		m_World.scale(m_Scale);
		m_World.translate(m_Origin * -1.0f);
	}

} // namespace fz
