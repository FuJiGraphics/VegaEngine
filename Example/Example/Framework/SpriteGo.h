#pragma once
#include "GameObject.h"

class SpriteGo : public GameObject
{
public:
	explicit SpriteGo(const std::string& name, const std::string& textureID);
	~SpriteGo() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void SetPosition(const sf::Vector2f& pos) override;
	void Draw(sf::RenderWindow& window) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& origin) override;

protected:
	sf::Sprite Sprite;
	std::string TexID;
};

