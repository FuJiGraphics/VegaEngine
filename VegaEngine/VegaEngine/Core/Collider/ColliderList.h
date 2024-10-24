#pragma once
#include "Core/Core.h"
#include "Core/Array.h"
#include "HitData.h"
#include "Collider.h"

namespace fz {
	
	class Window;
	class Layer;

	class ColliderList final : public Array<HitData>
	{
	//// Delete, Enum, Using
	protected:
		// Delete
		ColliderList(const ColliderList&) = delete;
		void operator=(const ColliderList&) = delete;

	//// Member Functions
	public:
		// Constructor, Destructor
		ColliderList();
		virtual ~ColliderList();

		// impl
		bool insert_safety(fz::Layer* layer);
		void insert(fz::Layer* layer);
		void insert(fz::Layer* layer, const sf::FloatRect& rect);
		Iter remove(fz::Layer* layer);

		void Display(fz::Window& window);
		void Release();
	};

} // namespace fz