#pragma once
#include <VegaEngine2.h>

namespace fz {

	class PlayerBody : public VegaScript
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
			transformComp.Transform.SetTranslate(5.f, -6.f);

			Animations.insert({ "Idle", {} });
			Animations["Idle"].id = "Idle";
			Animations["Idle"].fps = 4;
			Animations["Idle"].loopType = AnimationLoopTypes::PingPong;
			Animations["Idle"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 10, 260, 32, 32 } });
			Animations["Idle"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 44, 260, 32, 32 } });
			Animations["Idle"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 78, 260, 32, 32 } });
			Animations["Idle"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 113, 260, 32, 32 } });
			Animator.Play(&Animations["Idle"]);
		}

		void OnDestroy()
		{

		}

		void OnUpdate(float dt)
		{
			Animator.Update(dt);
		}

	private:

	};

} // namespace fz

BIND_SCRIPT(PlayerBody, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Body", PlayerBody);