#pragma once

#include "Core/Core.h"
#include "Core/Event/Event.h"
#include "Core/Collider/Collider.h"
#include "Core/Collider/HitData.h"
#include "Core/Camera/Camera.h"

namespace fz {

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
		virtual void OnDraw(Camera& camera);
		virtual void OnGui();
		virtual void OnCollide(const HitData& hit);

		// Inlines
		inline bool IsActivated() const						{ return m_IsActivate; }
		inline sf::Vector2f GetOrigin() const				{ return m_Origin; }
		inline sf::Vector2f GetPosition() const				{ return m_Pos; }
		inline sf::Vector2f GetScale() const				{ return m_Scale; }
		inline sf::Vector2u GetSize() const					{ return m_Size; }
		inline void SetActivate(bool enabled)				{ m_IsActivate = enabled; }
		inline void SetOrigin(const sf::Vector2f& origin)	{ m_Origin = origin; }
		inline void SetPosition(const sf::Vector2f& pos) 	{ m_Pos = pos; }
		inline void SetScale(const sf::Vector2f& scale)		{ m_Scale = scale; }
		inline void SetSize(const sf::Vector2u& size) 		{ m_Size = size; }

	//// Member Variables
	protected:
		sf::Vector2f m_Origin;
		sf::Vector2f m_Pos;
		sf::Vector2f m_Scale;
 		sf::Vector2u m_Size;
		bool m_IsActivate;
	};

} // namespace fz