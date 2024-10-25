#pragma once
#include "Core/Core.h"

namespace fz {

	class Utils
	{
	public:
		/*
		* @brief 랜덤 값을 리턴합니다.
		* @param[in] int start: 범위 시작 값
		* @param[in] int end: 범위 끝 값
		* @return int: 범위안의 값을 균일 분포로 랜덤 값을 리턴합니다.
		*/
		static int GetRandom(int start, int end);
		/*
		* @brief 랜덤 값을 리턴합니다.
		* @param[in] float start: 범위 시작 값
		* @param[in] float end: 범위 끝 값
		* @return float: 범위안의 값을 균일 분포로 랜덤 값을 리턴합니다.
		*/
		static float GetRandom(float min, float max);
		/*
		* @brief 360도 범위안의 랜덤한 위치(0.0f ~ 1.0f)를 반환합니다.
		* @return fz::Vec2f: 360도 범위 안의 랜덤 위치(0.0f ~ 1.0f)
		*/
		static fz::Vec2f RandomInUnitCircle();

	private:
		/*
		* @brief 파이 값
		* 
		*/
		static const float s_PI;
	};

} // namespace fz