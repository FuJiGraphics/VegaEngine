#pragma once
#include "Core/Core.h"

namespace fz {
	
	class Layer;

	struct Rect
	{
		int x, y;
		int w, h;
	};

	class Collider final
	{
	//// Delete, Enum, Using
	protected:
		// Using
		using Super = Collider;

		// Delete
		Collider(const Collider&) = delete;
		void operator=(const Collider&) = delete;

	//// Member Functions
	public:
		// Constructor, Destrcutor
		Collider();
		virtual ~Collider();
		
		// inlines
		inline void SetDisplay(bool enabled)				{ m_isDisplay = enabled; }
		inline void SetOutlineColor(const sf::Color& color) { m_Box.setOutlineColor(color); }
		inline void SetActivate(bool enabled)				{ m_isActivate = enabled; }
		inline bool IsDisplay() const						{ return m_isDisplay; }
		inline bool IsActivated() const						{ return m_isActivate; }
		inline const Rect& Get() const						{ return m_rect; }
		inline const sf::RectangleShape& GetBox() const		{ return m_Box; }

		// Impl
		void SetPosition(const sf::Vector2f& origin, const sf::FloatRect& rect, const sf::Vector2f& scale);
		void SetPosition(const Layer* layer);
		bool IsCollided(Collider& other);

	//// Member Variables
	private:
		sf::RectangleShape m_Box;
		bool m_isActivate;
		bool m_isDisplay;
		Rect m_rect;
	};

}