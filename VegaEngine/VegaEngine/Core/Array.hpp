#pragma once
#include "Array.h"

namespace fz {

	template<typename T>
	inline Array<T>::Array()
		: m_Array()
		, m_LeftEnd(m_Array.end())
		, m_LeftSize(0)
		, m_RightBegin(m_Array.end())
		, m_RightSize(0)
	{
		// Empty
	}

	template<typename T>
	inline Array<T>::~Array()
	{
		// Empty
	}

	template<typename T>
	inline void Array<T>::Insert(T data, Section place)
	{
		switch (place)
		{
			case Section::Left: 
				this->InsertLeft(data);
				break;
			case Section::Right:
				this->InsertRight(data);
		}
	}

	template<typename T>
	inline Array<T>::Iter Array<T>::Remove(T data, Section place)
	{
		Iter result;
		switch (place)
		{
			case Section::Left:
				result = this->RemoveLeft(data);
				break;
			case Section::Right:
				result = this->RemoveRight(data);
		}
		return result;
	}

	template<typename T>
	inline Array<T>::Iter Array<T>::Find(const T& target)
	{
		Array<T>::Iter iter = m_Array.end();
		for (auto layer : m_Array)
		{
			if (layer == target)
			{
				iter = layer;
				break;
			}
		}
		return iter;
	}

	template<typename T>
	inline void Array<T>::InsertLeft(const T& data)
	{
		m_Array.insert(m_LeftEnd, data);
		m_LeftEnd++;
		m_LeftSize++;
	}

	template<typename T>
	inline void Array<T>::InsertRight(const T& data)
	{
		m_Array.emplace_back(data);
		if (m_RightSize == 0)
			m_RightBegin = m_Array.begin();
		m_RightSize++;
	}

	template<typename T>
	inline Array<T>::Iter Array<T>::RemoveLeft(const T& data)
	{
		auto find = this->Find(m_Array.begin(), m_LeftEnd,
			[&data](Iter& target)
			{
				return (data == target);
			});
		if (find != m_LeftEnd)
		{
			find = m_Array.erase(find);
		}
		return (find == m_RightBegin) ?
			m_Array.end() : find;
	}

	template<typename T>
	inline Array<T>::Iter Array<T>::RemoveRight(const T& data)
	{
		auto find = this->Find(m_RightBegin, m_Array.end(),
			[&data](Iter& target)
			{
				return (data == target);
			});
		if (find != m_Array.end())
		{
			find = m_Array.erase(find);
		}
		return (find);
	}

	template<typename T>
	template<typename Fn>
	inline Array<T>::Iter Array<T>::Find(Iter first, Iter last, Fn pred)
	{
		Iter result = first;
		for (result; result != last; ++result)
		{
			if (pred(*result)) {
				break;
			}
		}
		return result;
	}

} // namespace fz