#pragma once
#include "VegaEngine2.h"

namespace fz {

	class Player : public ScriptableEntity
	{
	public:
		float Speed = 100.f;
		sf::RectangleShape Place;

		void OnCreate()
		{

		}

		void OnDestroy()
		{
		}

		void OnUpdate(float dt)
		{
			auto& transformComponent = GetComponent<TransformComponent>();
			
		};
	};
}

BIND_SCRIPT(Player, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Player", Player);
