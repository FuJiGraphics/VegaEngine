#pragma once
#include "VegaEngine2.h"

namespace fz {

	class Player : public ScriptableEntity
	{
	public:
		float Speed = 100.f;

		void OnCreate()
		{
			
		}

		void OnDestroy()
		{
		}

		void OnUpdate(float dt)
		{
			float h = InputManager::GetAxis(Axis::Horizontal);
			float v = InputManager::GetAxis(Axis::Vertical);
			if (HasComponent<RigidbodyComponent>())
			{
				auto& body = GetComponent<RigidbodyComponent>();
				sf::Vector2f dir = { h, v };

				sf::Vector2f groundNormal;
				if (body.IsOnGround(groundNormal))
				{
					dir = Utils::ProjectOnSlope(dir, groundNormal);
					body.SetGravityScale(4.0f);
				}

				body.SetLinearVelocity(dir * Speed);
				//body.AddForce((dir) * Speed);
			}
		};
	};
}

BIND_SCRIPT(Player, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Player", Player);
