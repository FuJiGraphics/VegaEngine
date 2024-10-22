#pragma once
#include "Core/Core.h"
#include "Core/Array.h"
#include "Core/Layer/Layer.h"
#include "Collider.h"
#include "HitData.h"

namespace fz {
	
	class ColliderList : Array<HitData>
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
		bool insert_safety(Layer* layer, Collider* collider);
		void insert(Layer* layer, Collider* collider);
		Iter remove(Layer* layer, Collider* collider);
	};

} // namespace fz