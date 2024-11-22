#pragma once
#include <VegaEngine2.h>

namespace fz {

	class PlayerLeg : public VegaScript
	{
	public:
		Animator Animator;
		std::unordered_map<std::string, fz::AnimationClip> Animations;

		void OnCreate()
		{
			auto& spriteComp = GetComponent<SpriteComponent>();
			sf::Sprite& sprite = spriteComp;
			auto& transformComp = GetComponent<TransformComponent>();
			Animator.SetTarget(&sprite);
			Animator.SetSpeed(1.5f);
			transformComp.Transform.SetTranslate(-1.f, 9.f);

			//Animations.insert({ "Idle", {} });
			//Animations["Idle"].id = "Idle";
			//Animations["Idle"].fps = 1;
			//Animations["Idle"].loopType = AnimationLoopTypes::Loop;
			//Animations["Idle"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 149, 276, 21, 16 } });
			//Animator.Play(&Animations["Idle"]);
		}

		void OnDestroy()
		{

		}

		void OnUpdate(float dt)
		{
			if (!HasComponent<SpriteComponent>())
				return;
			//Animator.Update(dt);
		}
	private:

	};

} // namespace fz


BIND_SCRIPT(PlayerLeg, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Leg", PlayerLeg);