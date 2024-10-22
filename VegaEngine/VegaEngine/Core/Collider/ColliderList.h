#pragma once
#include "Core/Core.h"
#include "Core/Array.h"
#include "Core/Layer/Layer.h"
#include "Collider.h"
#include "HitData.h"

namespace fz {
	
	class ColliderList final : Array<HitData>
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
		bool insert_safety(Layer* layer);
		void insert(Layer* layer);
		Iter remove(Layer* layer);

		void Release();
	};

} // namespace fz