#pragma once
#include "Core/Core.h"

namespace fz {

	class Utils
	{
	public:
		/*
		* @brief ���� ���� �����մϴ�.
		* @param[in] int start: ���� ���� ��
		* @param[in] int end: ���� �� ��
		* @return int: �������� ���� ���� ������ ���� ���� �����մϴ�.
		*/
		static int GetRandom(int start, int end);
		/*
		* @brief ���� ���� �����մϴ�.
		* @param[in] float start: ���� ���� ��
		* @param[in] float end: ���� �� ��
		* @return float: �������� ���� ���� ������ ���� ���� �����մϴ�.
		*/
		static float GetRandom(float min, float max);
		/*
		* @brief 360�� �������� ������ ��ġ(0.0f ~ 1.0f)�� ��ȯ�մϴ�.
		* @return fz::Vec2f: 360�� ���� ���� ���� ��ġ(0.0f ~ 1.0f)
		*/
		static fz::Vec2f RandomInUnitCircle();

	private:
		/*
		* @brief ���� ��
		* 
		*/
		static const float s_PI;
	};

} // namespace fz