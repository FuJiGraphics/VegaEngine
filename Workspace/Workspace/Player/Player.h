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
			if (HasComponent<RigidbodyComponent>())
			{
				auto& body = GetComponent<RigidbodyComponent>();
				sf::Vector2f velocity = body.GetLinearVelocity();
				sf::Vector2f movement;

				if (InputManager::IsKeyPressed(KeyType::A))
					movement = { Speed * -1.0f, velocity.y };
				else if (InputManager::IsKeyPressed(KeyType::D))
					movement = { Speed, velocity.y };
				else
					movement = { 0, velocity.y };

				body.SetLinearVelocity(movement);


			}
		};
	};
}

BIND_SCRIPT(Player, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Player", Player);
