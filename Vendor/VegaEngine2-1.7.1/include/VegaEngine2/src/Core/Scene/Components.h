#pragma once
#include <SFML/Graphics.hpp>
#include <Renderer/Camera.h>
#include "ScriptableEntity.h"
#include <functional>

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