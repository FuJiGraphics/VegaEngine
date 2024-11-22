#pragma once
#include <SFML/Graphics.hpp>
#include <Renderer/Camera.h>
#include "VegaScript.h"
#include <functional>

namespace fz {

	struct RootEntityComponent
	{
		fz::Entity RootEntity;

		RootEntityComponent() = default;
		RootEntityComponent(const RootEntityComponent&) = default;
		RootEntityComponent(const fz::Entity& other)
			: RootEntity(other)
		{/*Empty*/}
	};

	struct ChildEntityComponent
	{
		fz::Entity ParentEntity;
		std::vector<fz::Entity> CurrentChildEntities;

		ChildEntityComponent() = default;
		ChildEntityComponent(const ChildEntityComponent&) = default;
		ChildEntityComponent(const fz::Entity& other)
			: ParentEntity(other)
		{/*Empty*/}
	};

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
		sf::Transform RenderTransform;
		bool IsChildRenderMode = false;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const fz::Transform& other)
			: Transform(other)
		{/*Empty*/}

		operator fz::Transform& () { return Transform; }
		operator const fz::Transform& () const { return Transform; }
	};

	struct SpriteComponent
	{
		int SortingOrder = 0;
		fz::Sprite Sprite;

		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const fz::Sprite& other)
			: Sprite(other)
		{/*Empty*/}

		operator sf::Sprite& () { return Sprite; }
		operator const sf::Sprite& () const { return Sprite; }
	};

	struct CameraComponent
	{
		OrthoCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false; //∞Ì¡§ ¡æ»æ∫Ò(Fixed Aspect Ratio)

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const OrthoCamera& camera)
			: Camera(camera)
		{/*Empty*/}
		CameraComponent(const sf::Vector2f& center, const sf::Vector2f& size)
			: Camera(center, size)
		{/*Empty*/}

		inline operator OrthoCamera& ()				{ return Camera; }
		inline operator const OrthoCamera& () const	{ return Camera; }
	};

	struct RigidbodyComponent
	{
	protected:
		friend fz::Scene;
		void* RuntimeBody = nullptr;

	public:
		enum class BodyType {
			Static, Dynamic, Kinematic
		};
		BodyType RigidType = BodyType::Static;
		bool FixedRotation = false;

		void AddForce(const sf::Vector2f& force);
		void SetGravityScale(float scale);
		void SetLinearVelocity(const sf::Vector2f& velocity);
		sf::Vector2f GetLinearVelocity() const;

		bool IsOnGround();
		bool IsOnGround(sf::Vector2f& normal);
		bool IsOnGround(sf::Vector2f& normal, sf::Vector2f& pos);
		bool IsOnGround(sf::Vector2f& normal, sf::Vector2f& pos, float& fraction);

		RigidbodyComponent() = default;
		RigidbodyComponent(const RigidbodyComponent& other) = default;
	}; 

	struct BoxCollider2DComponent
	{
	protected:
		friend fz::Scene;
		void* RuntimeFixture = nullptr;

	public:
		sf::Vector2f Offset = { 0.0f, 0.0f };
		sf::Vector2f Size = { 0.5f, 0.5f };

		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent& other) = default;
	};

	struct NativeScriptComponent
	{
	public:

		VegaScript* Instance = nullptr;

		VegaScript* (*CreateInstanceFunc)();
		void (*DeleteInstanceFunc)(VegaScript* instance);

		void(*OnCreateFunction)(VegaScript*);
		void(*OnDestroyFunction)(VegaScript*);
		void(*OnUpdateFunction)(VegaScript*, float);

		template <typename T>
		void Bind()
		{
			CreateInstanceFunc = []() { return static_cast<VegaScript*>(new T()); };
			DeleteInstanceFunc = [](VegaScript* instance) { delete (T*)instance; instance = nullptr; };

			OnCreateFunction = [](VegaScript* instance) { ((T*)instance)->OnCreate(); };
			OnDestroyFunction = [](VegaScript* instance) { ((T*)instance)->OnDestroy(); };
			OnUpdateFunction = [](VegaScript* instance, float dt) { ((T*)instance)->OnUpdate(dt); };
		}
	};


} // namespace fz