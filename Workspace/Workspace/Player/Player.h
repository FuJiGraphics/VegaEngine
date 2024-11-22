#pragma once
#include "VegaEngine2.h"
#include "PlayerStatus.h"

namespace fz {

	class Player : public VegaScript
	{
	protected:
		using AnimType = PlayerStatus::Type;
		AnimType& CurrentType = PlayerStatus::Status;

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
			float fx = Input::GetAxis(Axis::Horizontal);

			body.SetGravityScale(0.75f);
			sf::Vector2f velocity = body.GetLinearVelocity();
			sf::Vector2f movement;

			const auto& scale = transform.Transform.GetScale();
			if (InputManager::IsKeyPressed(KeyType::D))
			{
				CurrentType = AnimType::Move;
				movement = { Speed * fx, velocity.y };
				if (body.IsOnGround())
				{
					float scaleX = (scale.x * -1.0f > 0.0f) ? scale.x * -1.0f : scale.x;
					transform.Transform.SetScale(scaleX, scale.y);
					if (InputManager::IsKeyPressed(KeyType::Space))
					{
						movement = { velocity.x, JumpPower };
					}
				}
			}
			else if (InputManager::IsKeyPressed(KeyType::A))
			{
				CurrentType = AnimType::Move;
				movement = { Speed * fx, velocity.y };
				if (body.IsOnGround())
				{
					float scaleX = (scale.x * -1.0f < 0.0f) ? scale.x * -1.0f : scale.x;
					transform.Transform.SetScale(scaleX, scale.y);
					if (InputManager::IsKeyPressed(KeyType::Space))
					{
						movement = { velocity.x, JumpPower };
					}
				}
			}
			else
			{
				movement = { 0, velocity.y };
				if (body.IsOnGround())
					CurrentType = AnimType::Idle;
			}

			if (body.IsOnGround())
			{
				if (InputManager::IsKeyPressed(KeyType::Space))
				{
					CurrentType = AnimType::IdleJump;
					movement = { velocity.x, JumpPower };
				}
			}
			body.SetLinearVelocity(movement);
		};
	};
}

BIND_SCRIPT(Player, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Player", Player);
