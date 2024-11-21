#pragma once
#include "VegaEngine2.h"

namespace fz {

	class Player : public VegaScript
	{
	public:
		float Speed = 110.f;
		float JumpPower = -300.f;

		void OnCreate()
		{
			
		}

		void OnDestroy()
		{

		}

		void OnUpdate(float dt)
		{
			auto& body = GetComponent<RigidbodyComponent>();
			auto& transform = GetComponent<TransformComponent>();
			body.SetGravityScale(0.75f);
			sf::Vector2f velocity = body.GetLinearVelocity();
			sf::Vector2f movement;

			const auto& scale = transform.Transform.GetScale();
			if (InputManager::IsKeyPressed(KeyType::A))
			{
				movement = { Speed * -1.0f, velocity.y };
				float scaleX = (scale.x * -1.0f < 0.0f) ? scale.x * -1.0f : scale.x;
				transform.Transform.SetScale(scaleX, scale.y);
			}
			else if (InputManager::IsKeyPressed(KeyType::D))
			{
				movement = { Speed, velocity.y };
				float scaleX = (scale.x * -1.0f > 0.0f) ? scale.x * -1.0f : scale.x;
				transform.Transform.SetScale(scaleX, scale.y);
			}
			else
				movement = { 0, velocity.y };

			if (body.IsOnGround())
			{
				if (InputManager::IsKeyPressed(KeyType::Space))
				{
					movement = { velocity.x, JumpPower };
				}
			}


			body.SetLinearVelocity(movement);
		};
	};
}

BIND_SCRIPT(Player, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Player", Player);
