#pragma once
#include <VegaEngine2.h>

namespace fz {

	class PlayerBody : public VegaScript
	{
	public:
		Animator Animator;
		std::unordered_map<std::string, fz::AnimationClip> Animations;
		bool IsPressedButton = false;

		void OnCreate()
		{
			auto& spriteComp = GetComponent<SpriteComponent>();
			sf::Sprite& sprite = spriteComp;
			auto& transformComp = GetComponent<TransformComponent>();
			Animator.SetTarget(&sprite);
			Animator.SetSpeed(1.5f);
			transformComp.Transform.SetTranslate(5.f, -1.f);

			Animations.insert({ "Idle", {} });
			Animations["Idle"].id = "Idle";
			Animations["Idle"].fps = 4;
			Animations["Idle"].loopType = AnimationLoopTypes::PingPong;
			Animations["Idle"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 10, 260, 32, 32 } });
			Animations["Idle"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 44, 260, 32, 32 } });
			Animations["Idle"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 78, 260, 32, 32 } });
			Animations["Idle"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 113, 260, 32, 32 } });
			Animator.Play(&Animations["Idle"]);
			

			Animations.insert({ "Move", {} });
			Animations["Move"].id = "Move";
			Animations["Move"].fps = 13;
			Animations["Move"].loopType = AnimationLoopTypes::PingPong;
			Animations["Move"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 10, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 47, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 82, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 115, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 147, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 181, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 216, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 254, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 291, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 328, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 364, 475, 32, 32 } });
			Animations["Move"].frames.push_back({ spriteComp.Sprite.GetOrigins(), { 400, 475, 32, 32 } });
		}

		void OnDestroy()
		{

		}

		void OnUpdate(float dt)
		{
			if (Input::IsKeyPressed(KeyType::A) || Input::IsKeyPressed(KeyType::D))
			{
				Animator.Play(&Animations["Move"]);
			}
			else
			{
				Animator.Play(&Animations["Idle"]);
			}

			Animator.Update(dt); 
			
		}

	private:

	};

} // namespace fz

BIND_SCRIPT(PlayerBody, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Body", PlayerBody);