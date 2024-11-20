#pragma once
#include <SFML/Graphics.hpp>
#include <Renderer/Camera.h>
#include "ScriptableEntity.h"
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
		enum class BodyType {
			Static, Dynamic, Kinematic
		};
		BodyType RigidType = BodyType::Dynamic;
		bool FixedRotation = false;

		void* RuntimeBody = nullptr;

		RigidbodyComponent() = default;
		RigidbodyComponent(const RigidbodyComponent& other) = default;
	}; 

	struct ColliderComponent
	{
		sf::Vector2f Offset = { 0.0f, 0.0f };
		sf::Vector2f Size = { 0.5f, 0.5f };

		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

		void* RuntimeFixture = nullptr;

		ColliderComponent() = default;
		ColliderComponent(const ColliderComponent& other) = default;
	};

	struct NativeScriptComponent
	{
	public:

		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*CreateInstanceFunc)();
		void (*DeleteInstanceFunc)(ScriptableEntity* instance);

		void(*OnCreateFunction)(ScriptableEntity*);
		void(*OnDestroyFunction)(ScriptableEntity*);
		void(*OnUpdateFunction)(ScriptableEntity*, float);

		template <typename T>
		void Bind()
		{
			CreateInstanceFunc = []() { return static_cast<ScriptableEntity*>(new T()); };
			DeleteInstanceFunc = [](ScriptableEntity* instance) { delete (T*)instance; instance = nullptr; };

			OnCreateFunction = [](ScriptableEntity* instance) { ((T*)instance)->OnCreate(); };
			OnDestroyFunction = [](ScriptableEntity* instance) { ((T*)instance)->OnDestroy(); };
			OnUpdateFunction = [](ScriptableEntity* instance, float dt) { ((T*)instance)->OnUpdate(dt); };
		}
	};


} // namespace fz