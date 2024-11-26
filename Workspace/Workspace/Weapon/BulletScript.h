#pragma once
#include <VegaEngine2.h>

namespace fz {

	class BulletScript : public VegaScript
	{
	public:
		float Speed = 500.f;

		void Start()
		{
		}

		void OnDestroy()
		{

		}

		void OnUpdate(float dt)
		{
			auto& transform = GetComponent<TransformComponent>();
			auto& body = GetComponent<RigidbodyComponent>();
			body.SetGravityScale(0.0f);

			float angle = transform.Transform.GetRotation();
			sf::Vector2f dir = Utils::Angle(angle);
			body.AddPosition({ Speed * dir.x, Speed * dir.y });
		}
		
	};

} // namespace fz

BIND_SCRIPT(BulletScript, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Bullet", BulletScript);

