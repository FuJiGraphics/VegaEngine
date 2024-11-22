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

		void OnCreate()
		{
			auto& spriteComp = GetComponent<SpriteComponent>();
			sf::Sprite& sprite = spriteComp;
			Animator.SetTarget(&sprite);
			Animator.SetSpeed(1.5f);
			const auto& origin = spriteComp.Sprite.GetOrigins();

			Animations["Idle"].id = "Idle";
			Animations["Idle"].fps = 1;
			Animations["Idle"].loopType = AnimationLoopTypes::Loop;
			Animations["Idle"].frames.push_back({ origin, { 148, 261, 25, 36 } });

			Animations["Move"].id = "Move";
			Animations["Move"].fps = 12;
			Animations["Move"].loopType = AnimationLoopTypes::Loop;
			Animations["Move"].frames.push_back({ origin, { 10, 536, 21, 20 } });
			Animations["Move"].frames.push_back({ origin, { 36, 536, 28, 20 } });
			Animations["Move"].frames.push_back({ origin, { 69, 536, 31, 16 } });
			Animations["Move"].frames.push_back({ origin, { 105, 536, 19, 20 } });
			Animations["Move"].frames.push_back({ origin, { 129, 536, 15, 20 } });
			Animations["Move"].frames.push_back({ origin, { 149, 536, 16, 20 } });
			Animations["Move"].frames.push_back({ origin, { 170, 536, 21, 20 } });
			Animations["Move"].frames.push_back({ origin, { 196, 536, 26, 20 } });
			Animations["Move"].frames.push_back({ origin, { 227, 536, 31, 16 } });
			Animations["Move"].frames.push_back({ origin, { 263, 536, 20, 20 } });
			Animations["Move"].frames.push_back({ origin, { 288, 536, 15, 20 } });
			Animations["Move"].frames.push_back({ origin, { 308, 536, 18, 20 } });

			Animations["IdleJump"].id = "IdleJump";
			Animations["IdleJump"].fps = 6;
			Animations["IdleJump"].loopType = AnimationLoopTypes::Loop;
			Animations["IdleJump"].frames.push_back({ origin, { 10, 894, 18, 24 } });
			Animations["IdleJump"].frames.push_back({ origin, { 33, 894, 19, 24 } });
			Animations["IdleJump"].frames.push_back({ origin, { 57, 894, 20, 24 } });
			Animations["IdleJump"].frames.push_back({ origin, { 81, 894, 20, 22 } });
			Animations["IdleJump"].frames.push_back({ origin, { 106, 894, 21, 19 } });
			Animations["IdleJump"].frames.push_back({ origin, { 132, 894, 21, 18 } });
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
					transform.SetTranslate(-1.f, 9.f);
					Animator.Play(&Animations["Idle"]);
					break;
				case AnimType::Move:
					transform.SetTranslate(-1.f, 14.f);
					Animator.Play(&Animations["Move"]);
					break;
				case AnimType::IdleJump:
					transform.SetTranslate(2.f, 19.f);
					Animator.Play(&Animations["IdleJump"]);
					break;
			}
		}
	private:

	};

} // namespace fz


BIND_SCRIPT(PlayerLeg, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Leg", PlayerLeg);