#pragma once

#include <SFML/Graphics.hpp>

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
		int operator()(int min, int max) const;
		/*
		* @brief ���� ���� �����մϴ�.
		* @param[in] float start: ���� ���� ��
		* @param[in] float end: ���� �� ��
		* @return float: �������� ���� ���� ������ ���� ���� �����մϴ�.
		*/
		float operator()(float min, float max) const;

		/*
		* @brief ���� ��(boolean)�� �����մϴ�.
		* @return bool: true �Ǵ� false�� �����մϴ�.
		*/
		bool Boolean() const;

		/*
		* @brief 360�� �������� ������ ��ġ(0.0f ~ 1.0f)�� ��ȯ�մϴ�.
		* @return sf::Vector2f: 360�� ���� ���� ���� ��ġ(0.0f ~ 1.0f)
		*/
		sf::Vector2f InUnitCircle() const;
		/*
		* @brief 360�� �������� ������ ��ġ(0.0f ~ 1.0f)�� ��ȯ�մϴ�.
		* @return sf::Vector2f: 360�� ���� ���� ���� ��ġ(0.0f ~ 1.0f)
		*/
		sf::Vector2f InUnitCircle();

		/*
		* @brief min �̻� max ������ base ���� ������ ������ ���� ���͸� ��ȯ�մϴ�.
		* @param[in] float min: ���� ���� ��
		* @param[in] float max: ���� �� ��
		* @param[base] sf::Vector2f base: ������ �Ǵ� ���� ���� (�⺻ �� x��)
		* @return min �̻� max ������ base ���� ������ ������ ���� ����
		*/
		sf::Vector2f Direction(float min, float max, const sf::Vector2f& base = sf::Vector2f(1.0f, 0.0f));

		std::string GetUUID() const;
	};

	/*< Random_internal ���� �ν��Ͻ� */
	static Random_internal& Random = Random_internal::GetInstance();

} // namespace fz
