#pragma once

class Utils
{
public:
	/* -----------------------------------------------------------
	* @brief		대상 오브젝트의 원점을 설정한다.
	* @param[out]	sf::Sprite& obj: 설정할 오브젝트 대상
	* @param[in]	Origins: 설정할 원점의 위치
	* @return		sf::Vector2f: 설정된 원점
	-----------------------------------------------------------*/
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins preset);
	/* -----------------------------------------------------------
	* @brief		대상 오브젝트의 원점을 설정한다.
	* @param[out]	sf::Text& obj: 설정할 오브젝트 대상
	* @param[in]	Origins: 설정할 원점의 위치
	* @return		sf::Vector2f: 설정된 원점
	-----------------------------------------------------------*/
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins preset);
};

