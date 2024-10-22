#include "Core/stdafx.h"
#include "ColliderArray.h"

namespace fz {

	void ColliderArray::Attach(Collider** collider)
	{
		if (this->Find(collider) == m_ColArray.end())
		{
			(*collider) = new Collider;
			m_ColArray.push_back(collider);
		}
	}

	void ColliderArray::Detach(Collider** collider)
	{
		auto target = this->Find(collider);
		if (target != m_ColArray.end())
		{
			m_ColArray.erase(target);
			delete (*collider);
			(*collider) = nullptr;
		}
	}

	ColliderArray::iter ColliderArray::Find(Collider** target)
	{
		return std::find_if(m_ColArray.begin(), m_ColArray.end(),
			[target](Collider** pTarget)
			{
				return (target == pTarget);
			});
	}

	ColliderArray::iter ColliderArray::begin()
	{
		return (m_ColArray.begin());
	}

	ColliderArray::iter ColliderArray::end()
	{
		return (m_ColArray.end());
	}

	ColliderArray::const_iter ColliderArray::begin() const
	{
		return (m_ColArray.begin());
	}

	ColliderArray::const_iter ColliderArray::end() const
	{
		return (m_ColArray.end());
	}

	ColliderArray::ColliderArray()
		: m_ColArray()
	{
		// Empty
	}

	ColliderArray::~ColliderArray()
	{
		for (auto collder : m_ColArray)
		{

		}
	}

	void ColliderArray::Init()
	{
	}

	void ColliderArray::Release()
	{
	}

} // namespace fz