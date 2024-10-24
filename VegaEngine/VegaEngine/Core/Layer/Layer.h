#pragma once

#include "Core/Core.h"
#include "Core/Event/Event.h"
#include "Core/Collider/Collider.h"
#include "Core/Collider/HitData.h"
#include "Core/Camera/Camera.h"

namespace fz {
	class Camera;

	struct CollideInfo
	{
		sf::Vector2f Position = { 0.0f, 0.0f };
		sf::Vector2u Size = { 0, 0 };
	};

	struct Object 
	{
		sf::Vector2f Origin = { 0.0f, 0.0f };
		sf::Vector2f Position = { 0.0f, 0.0f };
		sf::Vector2f Scale = { 1.0f, 1.0f };
		sf::Vector2u Size = { 0, 0 };
		sf::Sprite Sprite;
	};

	class Layer
	{
	//// Delete, Enum, Using
	protected:
		// Using
		using Super = Layer;

		// Delete
		Layer(const Layer&) = delete;
		void operator=(const Layer&) = delete;

	//// Member Functions
	public:
		// Constructor, Destructor
		Layer();
		virtual ~Layer();

		// ** Set ClassName **
		virtual std::string GetClassName() const = 0;

		// Virtuals 
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnEvent(fz::Event& event);
		virtual void OnUpdate(float dt);
		virtual void OnDraw(fz::Camera& camera);
		virtual void OnGui();
		virtual void OnCollide(const HitData& hit);

		// Inlines
		inline bool ActivatedDisplayCollider() const		{ return IsDisplayCollider; }
		inline Object& GetObject()							{ return Object; }
		inline const Object& GetObject() const				{ return Object; }
		inline bool IsActivated() const						{ return IsActivate; }
		inline sf::Vector2f GetOrigin() const				{ return Object.Origin; }
		inline sf::Vector2f GetPosition() const				{ return Object.Position; }
		inline sf::Vector2f GetScale() const				{ return Object.Scale; }
		inline sf::Vector2u GetSize() const					{ return Object.Size; }
		inline sf::Vector2f GetCollidePos() const			{ return CollideBox.Position; }
		inline sf::Vector2u GetCollideSize() const			{ return CollideBox.Size; }
		inline void SetObject(const Object& obj)			{ Object = obj; }
		inline void SetActivate(bool enabled)				{ IsActivate = enabled; }
		inline void SetOrigin(const sf::Vector2f& origin)	{ Object.Origin = origin; }
		inline void SetPosition(const sf::Vector2f& pos) 	{ Object.Position = pos; }
		inline void SetScale(const sf::Vector2f& scale)		{ Object.Scale = scale; }
		inline void SetSize(const sf::Vector2u& size) 		{ Object.Size = size; }


	//// Member Variables
	protected:
		bool IsDisplayCollider;
		bool IsActivate;
		Object Object;
		CollideInfo CollideBox;
	};

} // namespace fz