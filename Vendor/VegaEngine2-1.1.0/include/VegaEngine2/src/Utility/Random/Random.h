#pragma once

namespace fz {

	/*
	* @brief �������� ����� ����ϴ� static �Լ����� ��Ƴ��� Ŭ����
	* @details
	* - ��� ������� static ����, ���ǰ� �Ǿ��ֽ��ϴ�.
	* - ��� ���� �ӽ� ������ ��ȯ�˴ϴ�.
	* - ������ ��� �����ʹ� ������� �ʽ��ϴ�.
	*/
	class Random_internal final
	{
	public:
		static Random_internal& GetInstance();	/*< Random�� �ν��Ͻ��� �����մϴ�. */

		/*
		* @brief ���� ���� �����մϴ�.
		* @param[in] int start: ���� ���� ��
		* @param[in] int end: ���� �� ��
		* @return int: �������� ���� ���� ������ ���� ���� �����մϴ�.
		*/
		int operator()(int min, int max);
		/*
		* @brief ���� ���� �����մϴ�.
		* @param[in] float start: ���� ���� ��
		* @param[in] float end: ���� �� ��
		* @return float: �������� ���� ���� ������ ���� ���� �����մϴ�.
		*/
		float operator()(float min, float max);

		/*
		* @brief 360�� �������� ������ ��ġ(0.0f ~ 1.0f)�� ��ȯ�մϴ�.
		* @return fz::Vec2f: 360�� ���� ���� ���� ��ġ(0.0f ~ 1.0f)
		*/
		fz::Vec2f InUnitCircle() const;
		/*
		* @brief 360�� �������� ������ ��ġ(0.0f ~ 1.0f)�� ��ȯ�մϴ�.
		* @return fz::Vec2f: 360�� ���� ���� ���� ��ġ(0.0f ~ 1.0f)
		*/
		fz::Vec2f InUnitCircle();

	private:
		static const float s_PI;	/*< ���̰� */
	};

	/*< Random_internal ���� �ν��Ͻ� */
	static Random_internal& Random = Random_internal::GetInstance();

} // namespace fz
