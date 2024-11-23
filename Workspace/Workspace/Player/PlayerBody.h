#pragma once
#include <VegaEngine2.h>
#include "PlayerStatus.h"

namespace fz {

	class PlayerBody : public VegaScript
	{
	protected:
		using AnimType = PlayerStatus::Type;
		AnimType& CurrentType = PlayerStatus::Status;

	public:
		Animator Animator;
		std::unordered_map<std::string, fz::AnimationClip> Animations;
		bool IsPressedButton = false;

		void OnCreate()
		{
			auto& transformComp = GetComponent<TransformComponent>();
			auto& spriteComp = GetComponent<SpriteComponent>();
			sf::Sprite& sprite = spriteComp;
			Animator.SetTarget(sprite, transformComp);
			Animator.SetSpeed(2.0f);
			const auto& origin = spriteComp.Sprite.GetOrigins();

			Animations["Idle"].loadFromFile("animations/player_body_idle.json");
			Animations["Run"].loadFromFile("animations/player_body_run.json");
		}

		void OnDestroy()
		{

		}

		void OnUpdate(float dt)
		{
			auto& transform = GetComponent<TransformComponent>().Transform;
			Animator.Update(dt);

			switch (CurrentType)
			{
				case AnimType::Idle:
					Animator.Play(&Animations["Idle"]);
					break;
				case AnimType::Run:
					Animator.Play(&Animations["Run"]);
					break;
				case AnimType::IdleJump:
					//Animator.Play(&Animations["IdleJump"]);
					break;
			}
		}
	};

} // namespace fz

BIND_SCRIPT(PlayerBody, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Body", PlayerBody);