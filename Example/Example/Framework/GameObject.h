#pragma once

class GameObject
{
protected:
	std::string Name;
	bool Active;
	sf::Vector2f Position;
	sf::Vector2f Origin;
	Origins		 OriginPreset;

public:
	explicit GameObject(const std::string& name);
	virtual ~GameObject() = default;

	virtual void Init();
	virtual void Release();
	virtual void Reset();
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	virtual sf::Vector2f GetPosition() const { return Position; }
	virtual void SetPosition(const sf::Vector2f& pos) { Position = pos; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& origin);

	bool IsActive() const { return Active; }
	void SetActive(bool enable) { Active = enable; }
	std::string GetName() const { return (Name); }

	sf::Vector2f GetOrigin() const { return (Origin); }
};