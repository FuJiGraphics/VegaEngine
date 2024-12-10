#pragma once
#include "Core/Scene/Components.h"
#include "Core/Scene/VegaScript.h"

namespace fz {

	struct RaycastHit
	{
		Collider Collider;							// �浹�� ��ü�� Collider
		sf::Vector2f Point;							// �浹�� ���� ��ǥ
		sf::Vector2f Normal;						// �浹�� ǥ���� ��� ����
		float Distance;								// �浹 ���������� �Ÿ�
		fz::Transform Transform;					// �浹�� ����� Ʈ������
		RigidbodyComponent* Rigidbody = nullptr;	// �浹 ����� ������ٵ� ������Ʈ (���� ��� nullptr)
	};

	struct RayCastInfo
	{
		b2Fixture* Fixture = nullptr;
		b2Vec2 Point = { 0.f, 0.f };
		b2Vec2 Normal = { 0.f, 0.f };
		float Fraction = 0.f;
	};

	class RayCastCallback : public b2RayCastCallback
	{
	public:
		RayCastCallback();
		virtual ~RayCastCallback() = default;

		float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;
		RayCastInfo GetInfo() const;

		bool IsHitDetected() const { return m_HitDetected; }

	private:
		RayCastInfo m_Info;
		bool m_HitDetected;
	};

} // namespace fz
