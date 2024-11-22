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
			auto& spriteComp = GetComponent<SpriteComponent>();
			sf::Sprite& sprite = spriteComp;
			Animator.SetTarget(&sprite);
			Animator.SetSpeed(1.5f);
			const auto& origin = spriteComp.Sprite.GetOrigins();

			Animations["Idle"].id = "Idle";
			Animations["Idle"].fps = 4;
			Animations["Idle"].loopType = AnimationLoopTypes::PingPong;
			Animations["Idle"].frames.push_back({ origin, { 10, 260, 32, 32 } });
			Animations["Idle"].frames.push_back({ origin, { 44, 260, 32, 32 } });
			Animations["Idle"].frames.push_back({ origin, { 78, 260, 32, 32 } });
			Animations["Idle"].frames.push_back({ origin, { 113, 260, 32, 32 } });
			
			Animations["Move"].id = "Move";
			Animations["Move"].fps = 13;
			Animations["Move"].loopType = AnimationLoopTypes::Loop;
			Animations["Move"].frames.push_back({ origin, { 10, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ origin, { 47, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ origin, { 82, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ origin, { 115, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ origin, { 147, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ origin, { 181, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ origin, { 216, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ origin, { 254, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ origin, { 291, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ origin, { 328, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ origin, { 364, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ origin, { 400, 475, 32, 32 } });

			Animations["IdleJump"].id = "IdleJump";
			Animations["IdleJump"].fps = 6;
			Animations["IdleJump"].loopType = AnimationLoopTypes::Loop;
			Animations["IdleJump"].frames.push_back({ origin, { 10, 863, 29, 26 } });
			Animations["IdleJump"].frames.push_back({ origin, { 44, 863, 29, 25 } });
			Animations["IdleJump"].frames.push_back({ origin, { 79, 863, 29, 24 } });
			Animations["IdleJump"].frames.push_back({ origin, { 114, 863, 29, 23 } });
			Animations["IdleJump"].frames.push_back({ origin, { 147, 863, 29, 22 } });
			Animations["IdleJump"].frames.push_back({ origin, { 181, 863, 29, 23 } });
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
					transform.SetTranslate(5.f, -1.f);
					Animator.Play(&Animations["Idle"]);
					break;
				case AnimType::Move:
					Animator.Play(&Animations["Move"]);
					break;
			}
		}
	};

} // namespace fz

BIND_SCRIPT(PlayerBody, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Body", PlayerBody);