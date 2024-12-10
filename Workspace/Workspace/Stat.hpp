#pragma once
#include <VegaEngine2.h>

namespace fz {

	struct Stat
	{
		std::string Name = "None";
		std::string Class = "Hero";
		std::string Guild = "Kyungil";
		int Level = 15;				// ����
		int Experience = 0;			// ����ġ
		int Popularity = 0;			// �α⵵
		int HP = 100;				// �ִ� ü��
		int CurrentHP = HP;			// ���� ü��
		int MP = 100;				// ����
		int CurrentMP = MP;			// ���� ����
		int AttackPower = 10;		// ���ݷ�
		int PhysicalDefense = 0;	// ���� ����
		int MagicPower = 10;		// ����
		int MagicDefense = 0;		// ���� ����
		int Accuracy = 80;			// ���߷�
		int Evasion = 0;			// ȸ����
		int Dexterity = 0;			// ������
		int MoveSpeed = 100;		// �̵� �ӵ�
		int JumpPower = 500;		// ������

		int NumOfStr = 0;
		int NumOfDex = 0;
		int NumOfInt = 0;
		int NumOfLuk = 0;

		void ApplySTR(int STR) 
		{
			NumOfStr += STR;
			AttackPower += STR * 2;    // ���÷� STR�� ���� ���ݷ� ����
			PhysicalDefense += STR * 1; // STR�� ���� ���� ���� ����
			Accuracy += STR * 1;        // STR�� ���� ���߷� ����
		}

		void ApplyDEX(int DEX)
		{
			NumOfDex += DEX;
			Accuracy += DEX * 1;        // DEX�� ���� ���߷� ����
			Evasion += DEX * 1;         // DEX�� ���� ȸ���� ����
			Dexterity += DEX * 2;       // DEX�� ���� ������ ����
			MoveSpeed += DEX * 1;       // DEX�� ���� �̵� �ӵ� ����
		}

		void ApplyINT(int INT)
		{
			NumOfInt += INT;
			MagicPower += INT * 3;      // INT�� ���� ���� ����
			MagicDefense += INT * 2;    // INT�� ���� ���� ���� ����
		}

		void ApplyLUK(int LUK)
		{
			NumOfLuk += LUK;
			Evasion += LUK * 2;         // LUK�� ���� ȸ���� ����
			JumpPower += LUK * 1;       // LUK�� ���� ������ ����
		}
	};

	struct StatComponent
	{
	public:
		Stat Stat;

		StatComponent() = default;
		StatComponent(const StatComponent&) = default;
	};
} // namespace fz