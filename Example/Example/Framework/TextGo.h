#pragma once
#include "GameObject.h"

class TextGo : public GameObject
{
public:
	explicit TextGo(const std::string& name, const std::string& fontID);
	~TextGo() = default;

// overrides
	void Init() override;
	void Release() override;
	void Reset() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void Draw(sf::RenderWindow& window) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& origin) override;

// imgl
	void SetString(const std::string& text);

protected:
	sf::Text Text;
	std::string FontID;
};

