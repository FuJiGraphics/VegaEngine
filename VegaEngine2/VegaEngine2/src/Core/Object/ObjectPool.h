#pragma once
#include <list>

namespace fz {

	class Object;

	class ObjectPool
	{
	private:
		std::list<Object*> unused;
		std::list<Object*> used;
		int size;

	public:
		ObjectPool(int initSize = 100);
		virtual ~ObjectPool();

		template <typename T, typename ...Args>
		T* Take(Args&&... args);

		template <typename T>
		void Return(T* obj);
	};

} // namespace fz

#include "ObjectPool.hpp"