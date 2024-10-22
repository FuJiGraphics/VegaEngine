#pragma once
#include "Core/Core.h"
#include "Core/Layer/Layer.h"

namespace fz {
	
	struct Rect
	{
		int x, y;
		int w, h;
	};

	class Collider
	{
	//// Delete, Enum, Using
	protected:
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
		void Set(const sf::Vector2f& origin, const sf::FloatRect& rect, const sf::Vector2f& scale);
		bool IsCollided(Collider& other);

	//// Member Variables
	private:
		sf::RectangleShape m_Box;
		bool m_isActivate;
		bool m_isDisplay;
		Rect m_rect;
	};

}
