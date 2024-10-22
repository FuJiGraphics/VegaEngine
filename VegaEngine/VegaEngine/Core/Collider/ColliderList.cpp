#include "Core/stdafx.h"
#include "ColliderList.h"

namespace fz {

	ColliderList::ColliderList()
	{
		// Empty
	}

	ColliderList::~ColliderList()
	{
		this->Release();
		Super::clear();
	}

	bool ColliderList::insert_safety(Layer* layer)
	{
		bool result = false;
		Collider* collider;
		HitData findData = { layer, nullptr };
		Iter find = Super::find(Super::begin(), Super::end(),
			[&findData](HitData& target)
			{
				if (findData.ClassName() == target.ClassName())
					return true;
			}
		);
		if (find != Super::end())
		{
			collider = new Collider;
			collider->SetPosition(layer);
			Super::insert({ layer, collider });
			result = true;
		}
		return result;
	}

	void ColliderList::insert(Layer* layer)
	{
		Collider* collider = new Collider;
		collider->SetPosition(layer);
		Super::insert({ layer, collider });
	}

	ColliderList::Iter ColliderList::remove(Layer* layer)
	{
		Iter iter = Super::remove(Super::begin(), Super::end(),
			[&layer](HitData& target) {
				return (layer->GetClassName() == target.ClassName());
			});
		if (iter != Super::end())
		{
			iter->m_Class = nullptr;
			if (iter->m_Collider)
			{
				delete iter->m_Collider;
				iter->m_Collider = nullptr;
			}
		}
		return iter;
	}

	void ColliderList::Release()
	{
		for (auto& iter : *this)
		{
			iter.m_Class = nullptr;
			if (iter.m_Collider)
			{
				delete iter.m_Collider;
				iter.m_Collider = nullptr;
			}
		}
	}

} // namespace fz