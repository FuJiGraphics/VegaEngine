#pragma once
#include <VegaEngine2.h>

namespace fz {

	enum class PistolStatus
	{
		Idle = 0,
		Move, Jump, Crouch,

		MeleeAttack,

		CrouchAttack, CrouchAttackUp,
		IdleAttack, IdleAttackUp,
		JumpAttack, JumpAttackUp, JumpAttackDown,

		Count,
	};

	struct PistolFrame
	{
		sf::Sprite* Sprite;
		Shared<AnimationClip> Clip;
		float Speed;
	};

	class PistolStatusManager
	{
	public:
		static void Init();
		static void Update(float dt);

		static void AttachAnimClip(PistolStatus status, sf::Sprite* sprite, Shared<AnimationClip>& clip, float speed);

	private:
		inline static std::unordered_map<PistolStatus, std::vector<PistolFrame>>
			s_StatusMap;
		inline static std::unordered_map<KeyType, PistolStatus>
			S_PistolKeyMap;
		inline static Animator s_Animator;
	};

} // namespace fz
