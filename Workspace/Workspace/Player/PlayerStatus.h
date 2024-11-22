#pragma once
#include <VegaEngine2.h>

namespace fz {
	
	class PlayerStatus
	{
	public:
		enum class Type
		{
			Idle = 0, Move, Crouch,
			IdleJump,

			MeleeAttack,

			CrouchAttack, CrouchAttackUp,
			IdleAttack, IdleAttackUp,
			JumpAttack, JumpAttackUp, JumpAttackDown,

			Count,
		};

		inline static Type Status = Type::Idle;
	};

} // namespace fz
