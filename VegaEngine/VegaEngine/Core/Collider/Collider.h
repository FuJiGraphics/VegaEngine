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
		inline void SetOutlineColor(const sf::Color& color) { m_Box.setOutlineColor(color); }
		inline const Rect& GetRect() const					{ return m_rect; }
		inline Rect& GetRect()								{ return m_rect; }
		inline const sf::RectangleShape& GetBox() const		{ return m_Box; }
		inline sf::RectangleShape& GetBox()					{ return m_Box; }

		// Impl
		void SetPosition(const sf::FloatRect& rect);
		void SetPosition(const Layer* layer);
		bool IsCollided(Collider& other);
		bool IsCollided(const Collider& other) const;

	//// Member Variables
	private:
		sf::RectangleShape m_Box;
		Rect m_rect;
	};

}
