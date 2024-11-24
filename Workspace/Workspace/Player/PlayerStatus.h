#pragma once
#include <VegaEngine2.h>

namespace fz {
	
	class PlayerStatus
	{
	public:
		enum class Type
		{
			Idle,
			IdleJump,

			Run,
			RunJump,

			Crouch,
			MeleeAttack,

			CrouchAttack, CrouchAttackUp,
			IdleAttack, IdleAttackReflash, IdleAttackUp,
			JumpAttack, JumpAttackUp, JumpAttackDown,

			Count,
		};

		inline static Type Status = Type::Idle;
	};

} // namespace fz
