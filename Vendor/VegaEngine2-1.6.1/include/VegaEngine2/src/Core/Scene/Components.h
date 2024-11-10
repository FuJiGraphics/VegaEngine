#pragma once
#include <SFML/Graphics.hpp>

namespace fz {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& other)
			: Tag(other)
		{/*Empty*/}
	};

	struct TransformComponent
	{
		sf::Transform Transform = sf::Transform::Identity;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const sf::Transform& other)
			: Transform(other)
		{/*Empty*/}

		operator sf::Transform& () { return Transform; }
		operator const sf::Transform& () const { return Transform; }
	};

	struct SpriteComponent
	{
		sf::Sprite Sprite;

		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const sf::Sprite& other)
			: Sprite(other)
		{/*Empty*/}

		operator sf::Sprite& () { return Sprite; }
		operator const sf::Sprite& () const { return Sprite; }
	};

	struct RectangleComponent
	{
		sf::RectangleShape Rectangle;

		RectangleComponent() = default;
		RectangleComponent(const RectangleComponent&) = default;
		RectangleComponent(const sf::RectangleShape& other)
			: Rectangle(other)
		{/*Empty*/}

		operator sf::RectangleShape& () { return Rectangle; }
		operator const sf::RectangleShape& () const { return Rectangle; }
	};
}