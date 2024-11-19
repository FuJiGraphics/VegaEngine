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
			auto& transformComponent = GetComponent<TransformComponent>();
			auto& transform = transformComponent.Transform;
			auto prevPos = transform.GetTranslate();
			if (InputManager::IsKeyPressed(KeyType::W))
			{
				prevPos.y -= Speed * dt;
				transform.SetTranslate(prevPos);
			}
			if (InputManager::IsKeyPressed(KeyType::S))
			{
				prevPos.y += Speed * dt;
				transform.SetTranslate(prevPos);
			}
			if (InputManager::IsKeyPressed(KeyType::A))
			{
				prevPos.x -= Speed * dt;
				transform.SetTranslate(prevPos);
			}
			if (InputManager::IsKeyPressed(KeyType::D))
			{
				prevPos.x += Speed * dt;
				transform.SetTranslate(prevPos);
			}
		};
	};
}

BIND_SCRIPT(Player, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Player", Player);
