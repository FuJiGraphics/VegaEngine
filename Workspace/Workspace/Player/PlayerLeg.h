#pragma once
#include <VegaEngine2.h>
#include "PlayerStatus.h"

namespace fz {

	class PlayerLeg : public VegaScript
	{
	protected:
		using AnimType = PlayerStatus::Type;
		AnimType& CurrentType = PlayerStatus::Status;

	public:
		Animator Animator;
		std::unordered_map<std::string, fz::AnimationClip> Animations;

		void Start() override
		{
			auto& transformComp = GetComponent<TransformComponent>();
			auto& spriteComp = GetComponent<SpriteComponent>();
			sf::Sprite& sprite = spriteComp;
			Animator.SetTarget(sprite, transformComp);
			Animator.SetSpeed(2.0f);

			Animations["Idle"].loadFromFile("animations/player/player_leg_idle.json");
			Animations["Run"].loadFromFile("animations/player/player_leg_run.json");
			Animations["IdleJump"].loadFromFile("animations/player/player_leg_idle_jump.json");
			Animations["RunJump"].loadFromFile("animations/player/player_leg_run_jump.json");
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
					Animator.Play(&Animations["IdleJump"]);
					break;
				case AnimType::RunJump:
					Animator.Play(&Animations["RunJump"]);
					break;
			}
		}
	private:

	};

} // namespace fz


BIND_SCRIPT(PlayerLeg, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Leg", PlayerLeg);