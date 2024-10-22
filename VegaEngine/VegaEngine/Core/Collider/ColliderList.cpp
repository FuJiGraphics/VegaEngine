#include "Core/stdafx.h"
#include "ColliderList.h"

namespace fz {

	ColliderList::ColliderList()
	{
		// Empty
	}

	ColliderList::~ColliderList()
	{
		// Empty
	}

	bool ColliderList::insert_safety(Layer* layer, Collider* collider)
	{
		bool result = false;
		HitData findData = { layer, collider };
		Iter find = Super::find(Super::begin(), Super::end(),
			[&findData](HitData& target)
			{
				if (findData == target)
					return true;
			}
		);
		if (find != Super::end())
		{
			Super::insert({ layer, collider });
			result = true;
		}
		return result;
	}

	void ColliderList::insert(Layer* layer, Collider* collider)
	{
		Super::insert({ layer, collider });
	}

	ColliderList::Iter ColliderList::remove(Layer* layer, Collider* collider)
	{
		return Super::remove({ layer, collider });
	}

} // namespace fz