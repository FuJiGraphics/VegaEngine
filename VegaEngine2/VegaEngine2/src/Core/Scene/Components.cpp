#include "pch.h"

namespace fz {

	void RigidbodyComponent::AddForce(const sf::Vector2f& force)
	{
		((b2Body*)RuntimeBody)->ApplyForceToCenter(Utils::PixelToMeter(force), true);
	}

	void RigidbodyComponent::SetGravityScale(float scale)
	{
		((b2Body*)RuntimeBody)->SetGravityScale(scale);
	}

	void RigidbodyComponent::SetLinearVelocity(const sf::Vector2f& velocity)
	{
		((b2Body*)RuntimeBody)->SetLinearVelocity(Utils::PixelToMeter(velocity));
	}

	void RigidbodyComponent::AddPosition(const sf::Vector2f& pos)
	{
		sf::Vector2f velocity = this->GetLinearVelocity();
		float nextPosX = velocity.x;
		float nextPosY = velocity.y;
		// TODO: float ���� ��Ȯ�� ����
		if (pos.x != 0.0f)
			nextPosX = pos.x;
		if (pos.y != 0.0f)
			nextPosY = pos.y;
		this->SetLinearVelocity({ nextPosX, nextPosY });
	}

	sf::Vector2f RigidbodyComponent::GetLinearVelocity() const
	{
		return Utils::MeterToPixel(((b2Body*)RuntimeBody)->GetLinearVelocity());
	}

	bool RigidbodyComponent::IsOnGround(const sf::Vector2f& rayDir)
	{
		sf::Vector2f empty;
		float fempty;
		return IsOnGround(rayDir, empty, empty, fempty);
	}

	bool RigidbodyComponent::IsOnGround(const sf::Vector2f& rayDir, sf::Vector2f& normal)
	{
		sf::Vector2f empty;
		float fempty;
		return IsOnGround(rayDir, normal, empty, fempty);
	}

	bool RigidbodyComponent::IsOnGround(const sf::Vector2f& rayDir, sf::Vector2f& normal, sf::Vector2f& pos)
	{
		float fempty;
		return IsOnGround(rayDir, normal, pos, fempty);
	}

	bool RigidbodyComponent::IsOnGround(const sf::Vector2f& rayDir, sf::Vector2f& normal, sf::Vector2f& pos, float& fraction)
	{
		if (!FZ_CURRENT_SCENE)
			return false;
		void* rawWorld = FZ_CURRENT_SCENE->GetPhysicsWorld();
		if (rawWorld == nullptr)
			return false;

		class RayCastCallback : public b2RayCastCallback
		{
		public:
			RayCastCallback() = default;
			~RayCastCallback() = default;

			float Fraction = 0.0f;
			bool HitGround = false;
			sf::Vector2f Normal = { 0.0f, 0.0f };
			sf::Vector2f Position = { 0.0f, 0.0f };
			float ReportFixture(b2Fixture* f, const b2Vec2& p, const b2Vec2& n, float fraction) override
			{
				if (f->GetBody()->GetType() == b2_staticBody)
				{
  					HitGround = true;
   					Normal = { n.x, n.y };
					Position = Utils::MeterToPixel(p);
					Fraction = fraction;
					return 0.0f;  // �浹 �� �߰� �˻� ����
				}
				return 1.0f;  // ��� ����
			}
		};
		RayCastCallback callback;

		// ��ü�� ���� ��ġ
		b2Vec2 start = ((b2Body*)RuntimeBody)->GetPosition();
		// �ٴ����� 1���� ������ ��ġ
		b2Vec2 end = start - b2Vec2(rayDir.x, rayDir.y * -1.0f);

		bool hitGround = false;
		((b2World*)rawWorld)->RayCast(&callback, start, end);
		normal = callback.Normal;
		pos = callback.Position;
		hitGround = callback.HitGround;
 		return hitGround;
	}

	void BoxCollider2DComponent::SetTrigger(bool enabled)
	{
		IsTrigger = enabled;
		b2FixtureDef* fixture = (b2FixtureDef*)RuntimeFixture;
		fixture->isSensor = IsTrigger;
	}

	void EdgeCollider2DComponent::SetTrigger(bool enabled)
	{
		IsTrigger = enabled;
		b2FixtureDef* fixture = (b2FixtureDef*)RuntimeFixture;
		fixture->isSensor = IsTrigger;
	}

} // namespace fz
