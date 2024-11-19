#pragma once
#include "VegaEngine2.h"

namespace fz {

	class PlayerCamera : public ScriptableEntity
	{
	public:
		fz::Entity Player;
		sf::Vector2f Position;

		void OnCreate()
		{
		}

		void OnDestroy()
		{
		}

		void OnUpdate(float dt)
		{
			auto& transformComp = GetComponent<TransformComponent>();
			
			Position = transformComp.Transform.GetTranslate();




		};
	};
}

BIND_SCRIPT(PlayerCamera, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "PlayerCamera", PlayerCamera);
