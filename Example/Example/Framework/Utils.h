#pragma once

class Utils
{
public:
	/* -----------------------------------------------------------
	* @brief		��� ������Ʈ�� ������ �����Ѵ�.
	* @param[out]	sf::Sprite& obj: ������ ������Ʈ ���
	* @param[in]	Origins: ������ ������ ��ġ
	* @return		sf::Vector2f: ������ ����
	-----------------------------------------------------------*/
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins preset);
	/* -----------------------------------------------------------
	* @brief		��� ������Ʈ�� ������ �����Ѵ�.
	* @param[out]	sf::Text& obj: ������ ������Ʈ ���
	* @param[in]	Origins: ������ ������ ��ġ
	* @return		sf::Vector2f: ������ ����
	-----------------------------------------------------------*/
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins preset);
};
