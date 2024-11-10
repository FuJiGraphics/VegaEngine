#pragma once
#include <SFML/Graphics.hpp>
#include <Renderer/Camera.h>

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
		fz::Transform Transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const fz::Transform& other)
			: Transform(other)
		{/*Empty*/}

		operator fz::Transform& () { return Transform; }
		operator const fz::Transform& () const { return Transform; }
		fz::Transform* operator&() { return &Transform; }
		const fz::Transform* operator&() const { return &Transform; }
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
		sf::Sprite* operator&() { return &Sprite; }
		const sf::Sprite* operator&() const { return &Sprite; }
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
		sf::RectangleShape* operator&() { return &Rectangle; }
		const sf::RectangleShape* operator&() const { return &Rectangle; }
	};

	struct CameraComponent
	{
		OrthoCamera Camera;
		bool Primary = true;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const OrthoCamera& camera)
			: Camera(camera)
		{/*Empty*/}
		CameraComponent(const sf::Vector2f& center, const sf::Vector2f& size)
			: Camera(center, size)
		{/*Empty*/}

		operator OrthoCamera& () { return Camera; }
		operator const OrthoCamera& () const { return Camera; }
		OrthoCamera* operator&() { return &Camera; }
		const OrthoCamera* operator&() const { return &Camera; }
	};

} // namespace fz