#include "pch.h"
#include "ObjectPool.h"
#include "Object.h"

namespace fz {

	ObjectPool::ObjectPool(int initSize)
		: size(initSize)
	{
		// Empty
	}

	ObjectPool::~ObjectPool()
	{
		for (Object* obj : unused)
		{
			delete obj;
		}
		for (Object* obj : used)
		{
			delete obj;
		}
	}

} // namespace fz